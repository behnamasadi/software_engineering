// Factory Method — pick a Vehicle subtype by enum.

#include <iostream>
#include <memory>
#include <stdexcept>

class Vehicle {
public:
    virtual ~Vehicle() = default;
    virtual void describe() const = 0;
};

class Motorcycle : public Vehicle {
public:
    void describe() const override { std::cout << "  motorcycle (2 wheels)\n"; }
};

class Car : public Vehicle {
public:
    void describe() const override { std::cout << "  car (4 wheels)\n"; }
};

enum class VehicleType { Motorcycle, Car };

class VehicleFactory {
public:
    static std::unique_ptr<Vehicle> create(VehicleType type) {
        switch (type) {
            case VehicleType::Motorcycle: return std::make_unique<Motorcycle>();
            case VehicleType::Car:        return std::make_unique<Car>();
        }
        throw std::invalid_argument("Unknown vehicle type");
    }
};

int main() {
    VehicleFactory::create(VehicleType::Motorcycle)->describe();
    VehicleFactory::create(VehicleType::Car)->describe();
}
