#include <iostream>
#include <memory>

// Abstract Product: Vehicle
class Vehicle {
public:
    virtual void describe() const = 0;
    virtual ~Vehicle() = default;
};

// Concrete Product: Motorcycle
class Motorcycle : public Vehicle {
public:
    void describe() const override {
        std::cout << "🏍️ This is a motorcycle (Two-Wheeler)\n";
    }
};

// Concrete Product: Car
class Car : public Vehicle {
public:
    void describe() const override {
        std::cout << "🚗 This is a car (Four-Wheeler)\n";
    }
};

// Factory Class
class VehicleFactory {
public:
    static std::unique_ptr<Vehicle> createVehicle(int type) {
        if (type == 1) {
            return std::make_unique<Motorcycle>();
        } else if (type == 2) {
            return std::make_unique<Car>();
        } else {
            throw std::invalid_argument("Unknown vehicle type!");
        }
    }
};

// Main Function
int main() {
    try {
        std::unique_ptr<Vehicle> myBike = VehicleFactory::createVehicle(1);
        myBike->describe();

        std::unique_ptr<Vehicle> myCar = VehicleFactory::createVehicle(2);
        myCar->describe();
    } 
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
    }

    return 0;
}
