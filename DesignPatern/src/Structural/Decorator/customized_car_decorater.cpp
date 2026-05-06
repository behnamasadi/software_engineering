// Decorator — wrap a Car so add-ons (sound system, GPS, ...) can be stacked
// at runtime without subclassing every combination. Each decorator wraps a
// Car, forwards the call, and adds its own contribution.

#include <iomanip>
#include <iostream>
#include <memory>
#include <string>
#include <utility>

class Car {
public:
    virtual ~Car() = default;
    virtual std::string description() const = 0;
    virtual double price() const = 0;
};

class StandardCar : public Car {
public:
    std::string description() const override { return "Standard Model"; }
    double price() const override { return 35000.00; }
};

// Base decorator: holds the wrapped car and provides default forwarding.
// Concrete decorators override one or both methods to add their contribution.
class CarOption : public Car {
public:
    explicit CarOption(std::unique_ptr<Car> car) : car_(std::move(car)) {}

protected:
    std::unique_ptr<Car> car_;
};

class PremiumSound : public CarOption {
public:
    using CarOption::CarOption;
    std::string description() const override {
        return car_->description() + " + Premium Sound";
    }
    double price() const override { return car_->price() + 1200.00; }
};

class GPSNavigation : public CarOption {
public:
    using CarOption::CarOption;
    std::string description() const override {
        return car_->description() + " + GPS Navigation";
    }
    double price() const override { return car_->price() + 800.00; }
};

int main() {
    std::unique_ptr<Car> myCar = std::make_unique<StandardCar>();
    myCar = std::make_unique<PremiumSound>(std::move(myCar));
    myCar = std::make_unique<GPSNavigation>(std::move(myCar));

    std::cout << myCar->description() << '\n';
    std::cout << "Total Price: $" << std::fixed << std::setprecision(2)
              << myCar->price() << '\n';
}
