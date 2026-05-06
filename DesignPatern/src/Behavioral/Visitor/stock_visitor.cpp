// Visitor — buy/sell operations on a heterogeneous portfolio of stocks.
// Each Stock subclass exposes accept(Visitor&); concrete visitors decide what
// to do per stock type. Adding a new operation is a new visitor.

#include <iostream>
#include <memory>
#include <vector>

class Apple;
class Google;

class Visitor {
public:
    virtual ~Visitor() = default;
    virtual void visit(Apple& apple) = 0;
    virtual void visit(Google& google) = 0;
};

class Stock {
public:
    virtual ~Stock() = default;
    virtual void accept(Visitor& visitor) = 0;
};

class Apple : public Stock {
public:
    void accept(Visitor& visitor) override { visitor.visit(*this); }
    void buy()  { std::cout << "  Apple::buy\n"; }
    void sell() { std::cout << "  Apple::sell\n"; }
};

class Google : public Stock {
public:
    void accept(Visitor& visitor) override { visitor.visit(*this); }
    void buy()  { std::cout << "  Google::buy\n"; }
    void sell() { std::cout << "  Google::sell\n"; }
};

class BuyVisitor : public Visitor {
public:
    void visit(Apple& apple)   override { ++apple_;  apple.buy(); }
    void visit(Google& google) override { ++google_; google.buy(); }
    void report() const {
        std::cout << "bought: Apple=" << apple_ << ", Google=" << google_ << '\n';
    }
private:
    int apple_ = 0;
    int google_ = 0;
};

class SellVisitor : public Visitor {
public:
    void visit(Apple& apple)   override { ++apple_;  apple.sell(); }
    void visit(Google& google) override { ++google_; google.sell(); }
    void report() const {
        std::cout << "sold: Apple=" << apple_ << ", Google=" << google_ << '\n';
    }
private:
    int apple_ = 0;
    int google_ = 0;
};

int main() {
    std::vector<std::unique_ptr<Stock>> portfolio;
    portfolio.push_back(std::make_unique<Apple>());
    portfolio.push_back(std::make_unique<Google>());
    portfolio.push_back(std::make_unique<Google>());
    portfolio.push_back(std::make_unique<Apple>());
    portfolio.push_back(std::make_unique<Apple>());

    BuyVisitor buyer;
    for (const auto& stock : portfolio) stock->accept(buyer);
    buyer.report();

    SellVisitor seller;
    for (const auto& stock : portfolio) stock->accept(seller);
    seller.report();
}
