#include <iostream>
#include <memory>
#include <string>
#include <vector>

class Fruit;
class Book;

class ShoppingCartVisitor {
public:
    virtual ~ShoppingCartVisitor() = default;
    virtual int visit(const std::shared_ptr<Book>& book) = 0;
    virtual int visit(const std::shared_ptr<Fruit>& fruit) = 0;
};

class ItemElement {
public:
    virtual ~ItemElement() = default;
    virtual int accept(const std::shared_ptr<ShoppingCartVisitor>& visitor) = 0;
};

class Book : public ItemElement, public std::enable_shared_from_this<Book> {
private:
    int price;
    std::string isbnNumber;

public:
    Book(int cost, std::string isbn) : price(cost), isbnNumber(std::move(isbn)) {}

    int getPrice() const {
        return price;
    }

    std::string getIsbnNumber() const {
        return isbnNumber;
    }

    int accept(const std::shared_ptr<ShoppingCartVisitor>& visitor) override {
        return visitor->visit(shared_from_this());
    }
};

class Fruit : public ItemElement, public std::enable_shared_from_this<Fruit> {
private:
    int pricePerKg;
    int weight;
    std::string name;

public:
    Fruit(int priceKg, int wt, std::string nm) 
        : pricePerKg(priceKg), weight(wt), name(std::move(nm)) {}

    int getPricePerKg() const {
        return pricePerKg;
    }

    int getWeight() const {
        return weight;
    }

    std::string getName() const {
        return name;
    }

    int accept(const std::shared_ptr<ShoppingCartVisitor>& visitor) override {
        return visitor->visit(shared_from_this());
    }
};

class ShoppingCartVisitorImpl : public ShoppingCartVisitor {
public:
    int visit(const std::shared_ptr<Book>& book) override {
        int cost = book->getPrice();
        if (cost > 50) {
            cost -= 5; // Apply $5 discount if the book price is greater than 50
        }
        std::cout << "Book ISBN: " << book->getIsbnNumber() << " cost = " << cost << std::endl;
        return cost;
    }

    int visit(const std::shared_ptr<Fruit>& fruit) override {
        int cost = fruit->getPricePerKg() * fruit->getWeight();
        std::cout << fruit->getName() << " cost = " << cost << std::endl;
        return cost;
    }
};

class ShoppingCart {
private:
    std::vector<std::shared_ptr<ItemElement>> items;
    std::shared_ptr<ShoppingCartVisitor> visitor;

public:
    ShoppingCart() : visitor(std::make_shared<ShoppingCartVisitorImpl>()) {}

    void addItem(const std::shared_ptr<ItemElement>& item) {
        items.push_back(item);
    }

    int calculateTotal() const {
        int sum = 0;
        for (const auto& item : items) {
            sum += item->accept(visitor);
        }
        return sum;
    }
};

int main() {
    ShoppingCart cart;
    cart.addItem(std::make_shared<Book>(20, "1234"));
    cart.addItem(std::make_shared<Book>(100, "5678"));
    cart.addItem(std::make_shared<Fruit>(10, 2, "Banana"));
    cart.addItem(std::make_shared<Fruit>(5, 5, "Apple"));

    int total = cart.calculateTotal();
    std::cout << "Total Cost = " << total << std::endl;

    return 0;
}