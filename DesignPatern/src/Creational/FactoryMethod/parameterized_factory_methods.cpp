#include <iostream>
#include <memory>

// Abstract Product
class Product {
public:
    virtual ~Product() = default;
    virtual void use() const = 0;
};

// Concrete Product
class CustomProduct : public Product {
public:
    CustomProduct() { std::cout << "🔧 CustomProduct: Created\n"; }
    void use() const override { std::cout << "🛠️ Using CustomProduct\n"; }
};

// Abstract Creator
class Creator {
public:
    virtual std::unique_ptr<Product> createInstance() = 0;
    virtual ~Creator() = default;
};

// Concrete Creator (Factory) using Templates
template <class TheProduct>
class ProductFactory : public Creator {
public:
    std::unique_ptr<Product> createInstance() override {
        return std::make_unique<TheProduct>();
    }
};

// Main Function
int main() {
    // Create a factory for CustomProduct
    ProductFactory<CustomProduct> factory;

    // Create an instance of CustomProduct
    std::unique_ptr<Product> product = factory.createInstance();

    // Use the product
    product->use();

    return 0;
}
