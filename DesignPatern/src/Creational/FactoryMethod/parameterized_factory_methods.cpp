// Factory Method — parameterized over the product type.
// One template ProductFactory<T> generates a factory for any concrete Product
// without writing a new factory class for each.

#include <iostream>
#include <memory>

class Product {
public:
    virtual ~Product() = default;
    virtual void use() const = 0;
};

class CustomProduct : public Product {
public:
    CustomProduct() { std::cout << "  CustomProduct ctor\n"; }
    void use() const override { std::cout << "  using CustomProduct\n"; }
};

class AnotherProduct : public Product {
public:
    AnotherProduct() { std::cout << "  AnotherProduct ctor\n"; }
    void use() const override { std::cout << "  using AnotherProduct\n"; }
};

class Creator {
public:
    virtual ~Creator() = default;
    virtual std::unique_ptr<Product> create() = 0;
};

template <typename T>
class ProductFactory : public Creator {
    static_assert(std::is_base_of_v<Product, T>, "T must derive from Product");
public:
    std::unique_ptr<Product> create() override { return std::make_unique<T>(); }
};

int main() {
    ProductFactory<CustomProduct>  customFactory;
    ProductFactory<AnotherProduct> anotherFactory;

    customFactory.create()->use();
    anotherFactory.create()->use();
}
