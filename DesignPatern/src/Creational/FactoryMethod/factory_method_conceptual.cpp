// Factory Method — conceptual skeleton.
//
// ProductCreator declares a factory method (createProduct). Subclasses decide
// which Product to instantiate. Common business logic (generateReport) lives
// in the base class; only the type of product varies.

#include <iostream>
#include <memory>
#include <string>

class Product {
public:
    virtual ~Product() = default;
    virtual std::string info() const = 0;
};

class AlphaProduct : public Product {
public:
    std::string info() const override { return "AlphaProduct"; }
};

class BetaProduct : public Product {
public:
    std::string info() const override { return "BetaProduct"; }
};

class ProductCreator {
public:
    virtual ~ProductCreator() = default;

    // Factory Method.
    virtual std::unique_ptr<Product> createProduct() const = 0;

    // Business logic that uses the factory method.
    std::string generateReport() const {
        auto product = createProduct();
        return "report: worked with " + product->info();
    }
};

class AlphaCreator : public ProductCreator {
public:
    std::unique_ptr<Product> createProduct() const override {
        return std::make_unique<AlphaProduct>();
    }
};

class BetaCreator : public ProductCreator {
public:
    std::unique_ptr<Product> createProduct() const override {
        return std::make_unique<BetaProduct>();
    }
};

void clientProcess(const ProductCreator& creator) {
    std::cout << "  " << creator.generateReport() << '\n';
}

int main() {
    std::cout << "AlphaCreator:\n";
    clientProcess(AlphaCreator{});

    std::cout << "BetaCreator:\n";
    clientProcess(BetaCreator{});
}
