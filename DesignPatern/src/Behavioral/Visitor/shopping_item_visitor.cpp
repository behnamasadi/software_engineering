// Visitor — shopping cart pricing.
// Each item type (Book, Fruit) has accept(Visitor&); a PricingVisitor returns
// per-item cost. Different pricing rules = different visitors, no item changes.

#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

class Book;
class Fruit;

class CartVisitor {
public:
    virtual ~CartVisitor() = default;
    virtual int visit(const Book& book) = 0;
    virtual int visit(const Fruit& fruit) = 0;
};

class Item {
public:
    virtual ~Item() = default;
    virtual int accept(CartVisitor& visitor) const = 0;
};

class Book : public Item {
public:
    Book(int price, std::string isbn) : price_(price), isbn_(std::move(isbn)) {}
    int price() const { return price_; }
    const std::string& isbn() const { return isbn_; }
    int accept(CartVisitor& visitor) const override { return visitor.visit(*this); }
private:
    int price_;
    std::string isbn_;
};

class Fruit : public Item {
public:
    Fruit(int pricePerKg, int weight, std::string name)
        : pricePerKg_(pricePerKg), weight_(weight), name_(std::move(name)) {}
    int pricePerKg() const { return pricePerKg_; }
    int weight() const     { return weight_; }
    const std::string& name() const { return name_; }
    int accept(CartVisitor& visitor) const override { return visitor.visit(*this); }
private:
    int pricePerKg_;
    int weight_;
    std::string name_;
};

class PricingVisitor : public CartVisitor {
public:
    int visit(const Book& book) override {
        int cost = book.price();
        if (cost > 50) cost -= 5;  // bulk discount on pricier books
        std::cout << "  book " << book.isbn() << " = " << cost << '\n';
        return cost;
    }
    int visit(const Fruit& fruit) override {
        int cost = fruit.pricePerKg() * fruit.weight();
        std::cout << "  " << fruit.name() << " = " << cost << '\n';
        return cost;
    }
};

class ShoppingCart {
public:
    void add(std::unique_ptr<Item> item) { items_.push_back(std::move(item)); }

    int total() const {
        PricingVisitor pricer;
        int sum = 0;
        for (const auto& item : items_) sum += item->accept(pricer);
        return sum;
    }

private:
    std::vector<std::unique_ptr<Item>> items_;
};

int main() {
    ShoppingCart cart;
    cart.add(std::make_unique<Book>(20, "1234"));
    cart.add(std::make_unique<Book>(100, "5678"));
    cart.add(std::make_unique<Fruit>(10, 2, "Banana"));
    cart.add(std::make_unique<Fruit>(5, 5, "Apple"));

    int total = cart.total();
    std::cout << "total = " << total << '\n';
}
