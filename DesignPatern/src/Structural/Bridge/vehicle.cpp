// Bridge — Vehicle (abstraction) over Workshop (implementation).
//
// Two axes vary independently:
//   - Vehicles: Car, Bike, ...
//   - Workshops: Produce, Repair, ...
// A Vehicle composes a list of workshops and forwards `manufacture()` to each.
// New vehicles or workshops are added without touching the others.

#include <iostream>
#include <memory>
#include <utility>
#include <vector>

class Workshop {
public:
    virtual ~Workshop() = default;
    virtual void work() const = 0;
};

class Produce : public Workshop {
public:
    void work() const override { std::cout << "  produced"; }
};

class Repair : public Workshop {
public:
    void work() const override { std::cout << "  repaired"; }
};

class Vehicle {
public:
    Vehicle(std::unique_ptr<Workshop> a, std::unique_ptr<Workshop> b)
        : a_(std::move(a)), b_(std::move(b)) {}

    virtual ~Vehicle() = default;
    virtual void manufacture() const = 0;

protected:
    std::unique_ptr<Workshop> a_;
    std::unique_ptr<Workshop> b_;
};

class Car : public Vehicle {
public:
    using Vehicle::Vehicle;
    void manufacture() const override {
        std::cout << "Car";
        a_->work();
        b_->work();
        std::cout << '\n';
    }
};

class Bike : public Vehicle {
public:
    using Vehicle::Vehicle;
    void manufacture() const override {
        std::cout << "Bike";
        a_->work();
        b_->work();
        std::cout << '\n';
    }
};

int main() {
    std::vector<std::unique_ptr<Vehicle>> fleet;
    fleet.push_back(std::make_unique<Car>(std::make_unique<Produce>(),
                                          std::make_unique<Repair>()));
    fleet.push_back(std::make_unique<Bike>(std::make_unique<Produce>(),
                                           std::make_unique<Repair>()));

    for (const auto& v : fleet) v->manufacture();
}
