// Decorator — start with a base ice cream, then stack toppings (fruit, nuts,
// wafer, ...) at runtime. Each decorator wraps an IceCream, forwards `make()`
// to the wrapped object, and prints its own contribution after.

#include <iostream>
#include <memory>
#include <utility>

class IceCream {
public:
    virtual ~IceCream() = default;
    virtual void make() const = 0;
};

class BasicIceCream : public IceCream {
public:
    void make() const override {
        std::cout << "Milk + Sugar + Ice Cream Base";
    }
};

// Base decorator.
class IceCreamTopping : public IceCream {
public:
    explicit IceCreamTopping(std::unique_ptr<IceCream> inner)
        : inner_(std::move(inner)) {}

    void make() const override { inner_->make(); }

protected:
    std::unique_ptr<IceCream> inner_;
};

class FruitTopping : public IceCreamTopping {
public:
    using IceCreamTopping::IceCreamTopping;
    void make() const override {
        IceCreamTopping::make();
        std::cout << " + Fresh Fruits";
    }
};

class NutTopping : public IceCreamTopping {
public:
    using IceCreamTopping::IceCreamTopping;
    void make() const override {
        IceCreamTopping::make();
        std::cout << " + Crunchy Nuts";
    }
};

class WaferCrunch : public IceCreamTopping {
public:
    using IceCreamTopping::IceCreamTopping;
    void make() const override {
        IceCreamTopping::make();
        std::cout << " + Crispy Wafers";
    }
};

int main() {
    std::unique_ptr<IceCream> cone = std::make_unique<BasicIceCream>();
    cone->make(); std::cout << '\n';

    cone = std::make_unique<FruitTopping>(std::move(cone));
    cone->make(); std::cout << '\n';

    cone = std::make_unique<NutTopping>(std::move(cone));
    cone->make(); std::cout << '\n';

    cone = std::make_unique<WaferCrunch>(std::move(cone));
    cone->make(); std::cout << '\n';
}
