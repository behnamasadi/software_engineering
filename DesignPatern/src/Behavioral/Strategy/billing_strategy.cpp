// Strategy — pluggable algorithms for the same task.
// A checkout calculates a total using a discount strategy. Swapping the
// strategy at runtime changes the result without touching Checkout.

#include <iostream>
#include <memory>
#include <utility>

class DiscountStrategy {
public:
    virtual ~DiscountStrategy() = default;
    virtual double apply(double subtotal) const = 0;
};

class NoDiscount : public DiscountStrategy {
public:
    double apply(double subtotal) const override { return subtotal; }
};

class PercentageOff : public DiscountStrategy {
public:
    explicit PercentageOff(double percent) : percent_(percent) {}
    double apply(double subtotal) const override {
        return subtotal * (1.0 - percent_ / 100.0);
    }
private:
    double percent_;
};

class FlatOff : public DiscountStrategy {
public:
    explicit FlatOff(double amount) : amount_(amount) {}
    double apply(double subtotal) const override {
        return subtotal > amount_ ? subtotal - amount_ : 0.0;
    }
private:
    double amount_;
};

class Checkout {
public:
    explicit Checkout(std::unique_ptr<DiscountStrategy> d)
        : discount_(std::move(d)) {}

    void setDiscount(std::unique_ptr<DiscountStrategy> d) { discount_ = std::move(d); }

    double total(double subtotal) const { return discount_->apply(subtotal); }

private:
    std::unique_ptr<DiscountStrategy> discount_;
};

int main() {
    Checkout cart(std::make_unique<NoDiscount>());
    std::cout << "no discount:  " << cart.total(100) << '\n';

    cart.setDiscount(std::make_unique<PercentageOff>(15));
    std::cout << "15% off:      " << cart.total(100) << '\n';

    cart.setDiscount(std::make_unique<FlatOff>(20));
    std::cout << "$20 off:      " << cart.total(100) << '\n';
}
