#include <iostream>
#include <memory>
#include <string>

// Abstract Product
class Product {
public:
    virtual ~Product() = default;
    virtual std::string getInfo() const = 0;
};

// Concrete Product: Alpha
class AlphaProduct : public Product {
public:
    std::string getInfo() const override {
        return "{AlphaProduct: Advanced Processing}";
    }
};

// Concrete Product: Beta
class BetaProduct : public Product {
public:
    std::string getInfo() const override {
        return "{BetaProduct: Efficient Performance}";
    }
};

// Abstract Creator
class ProductCreator {
public:
    virtual ~ProductCreator() = default;
    
    // Factory Method using smart pointers
    virtual std::unique_ptr<Product> createProduct() const = 0;

    // Business logic using factory method
    std::string generateReport() const {
        auto product = this->createProduct();
        return "ProductCreator: Successfully worked with " + product->getInfo();
    }
};

// Concrete Creator: Alpha
class AlphaCreator : public ProductCreator {
public:
    std::unique_ptr<Product> createProduct() const override {
        return std::make_unique<AlphaProduct>();
    }
};

// Concrete Creator: Beta
class BetaCreator : public ProductCreator {
public:
    std::unique_ptr<Product> createProduct() const override {
        return std::make_unique<BetaProduct>();
    }
};

// Client Code
void clientProcess(const ProductCreator& creator) {
    std::cout << "Client: Executing process...\n"
              << creator.generateReport() << std::endl;
}

// Main Function
int main() {
    std::cout << "🚀 App: Running with AlphaCreator.\n";
    std::unique_ptr<ProductCreator> alphaCreator = std::make_unique<AlphaCreator>();
    clientProcess(*alphaCreator);
    
    std::cout << "\n🚀 App: Running with BetaCreator.\n";
    std::unique_ptr<ProductCreator> betaCreator = std::make_unique<BetaCreator>();
    clientProcess(*betaCreator);

    return 0;
}
