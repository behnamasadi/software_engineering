#include <iostream>
#include <vector>
#include <memory>

class Visitor; // Forward declaration

class Stock {
public:
    virtual ~Stock() = default;
    virtual void accept(std::shared_ptr<Visitor> visitor) = 0;
};

// Inherit from enable_shared_from_this so that you can safely call shared_from_this()
class Apple : public Stock, public std::enable_shared_from_this<Apple> {
public:
    void accept(std::shared_ptr<Visitor> visitor) override;
    void buy()  { std::cout << "Apple::buy\n"; }
    void sell() { std::cout << "Apple::sell\n"; }
};

class Google : public Stock, public std::enable_shared_from_this<Google> {
public:
    void accept(std::shared_ptr<Visitor> visitor) override;
    void buy()  { std::cout << "Google::buy\n"; }
    void sell() { std::cout << "Google::sell\n"; }
};

class Visitor {
protected:
    int num_apple  = 0;
    int num_google = 0;

public:
    virtual ~Visitor() = default;
    virtual void visit(std::shared_ptr<Apple> apple)   = 0;
    virtual void visit(std::shared_ptr<Google> google) = 0;

    void total_stocks() const {
        std::cout << "Total Apple stocks: " << num_apple 
                  << ", Total Google stocks: " << num_google << '\n';
    }
};

class BuyVisitor : public Visitor {
public:
    void visit(std::shared_ptr<Apple> apple) override {
        ++num_apple;
        apple->buy();
        std::cout << "Current Apple stocks: " << num_apple << '\n';
    }

    void visit(std::shared_ptr<Google> google) override {
        ++num_google;
        google->buy();
        std::cout << "Current Google stocks: " << num_google << '\n';
    }
};

class SellVisitor : public Visitor {
public:
    void visit(std::shared_ptr<Apple> apple) override {
        if (num_apple > 0) {
            --num_apple;
        }
        apple->sell();
        std::cout << "Current Apple stocks: " << num_apple << '\n';
    }

    void visit(std::shared_ptr<Google> google) override {
        if (num_google > 0) {
            --num_google;
        }
        google->sell();
        std::cout << "Current Google stocks: " << num_google << '\n';
    }
};

void Apple::accept(std::shared_ptr<Visitor> visitor) {
    // 'shared_from_this()' is valid because Apple inherits 'enable_shared_from_this<Apple>'
    visitor->visit(std::static_pointer_cast<Apple>(shared_from_this()));
}

void Google::accept(std::shared_ptr<Visitor> visitor) {
    // 'shared_from_this()' is valid because Google inherits 'enable_shared_from_this<Google>'
    visitor->visit(std::static_pointer_cast<Google>(shared_from_this()));
}

int main() {
    std::vector<std::shared_ptr<Stock>> stocks = {
        std::make_shared<Apple>(),
        std::make_shared<Google>(),
        std::make_shared<Google>(),
        std::make_shared<Apple>(),
        std::make_shared<Apple>()
    };

    auto buy_operation  = std::make_shared<BuyVisitor>();
    auto sell_operation = std::make_shared<SellVisitor>();

    for (const auto& stock : stocks) {
        stock->accept(buy_operation);
    }
    buy_operation->total_stocks();

    for (const auto& stock : stocks) {
        stock->accept(sell_operation);
    }
    sell_operation->total_stocks();

    return 0;
}
