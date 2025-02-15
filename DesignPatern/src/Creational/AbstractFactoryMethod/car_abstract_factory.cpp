#include <iostream>
#include <memory>
#include <string>

// Car Type Enumeration
enum class CarType
{
    MICRO, MINI, LUXURY
};

std::string ToString(CarType type)
{
    switch (type)
    {
        case CarType::MICRO:   return "MICRO";
        case CarType::MINI:    return "MINI";
        case CarType::LUXURY:  return "LUXURY";
        default:               return "[Unknown]";
    }
}

// Location Enumeration
enum class Location
{
    DEFAULT, USA, INDIA
};

std::string ToString(Location loc)
{
    switch (loc)
    {
        case Location::DEFAULT: return "DEFAULT";
        case Location::USA:     return "USA";
        case Location::INDIA:   return "INDIA";
        default:                return "[Unknown]";
    }
}

// Base Car Class
class Car
{
protected:
    CarType model;
    Location location;

public:
    Car(CarType model, Location location) : model(model), location(location) {}

    virtual void assemble() = 0;

    std::string getInfo() const
    {
        return "🚗 Car Model: " + ToString(model) + " | Location: " + ToString(location);
    }

    virtual ~Car() = default;
};

// Concrete Car Implementations
class LuxuryCar : public Car
{
public:
    LuxuryCar(Location location) : Car(CarType::LUXURY, location)
    {
        assemble();
    }

    void assemble() override
    {
        std::cout << "🔧 Assembling a Luxury Car\n";
    }
};

class MicroCar : public Car
{
public:
    MicroCar(Location location) : Car(CarType::MICRO, location)
    {
        assemble();
    }

    void assemble() override
    {
        std::cout << "🔧 Assembling a Micro Car\n";
    }
};

class MiniCar : public Car
{
public:
    MiniCar(Location location) : Car(CarType::MINI, location)
    {
        assemble();
    }

    void assemble() override
    {
        std::cout << "🔧 Assembling a Mini Car\n";
    }
};

// Car Factories for Different Regions
class IndiaCarFactory
{
public:
    static std::unique_ptr<Car> buildCar(CarType model)
    {
        switch (model)
        {
            case CarType::MICRO:  return std::make_unique<MicroCar>(Location::INDIA);
            case CarType::MINI:   return std::make_unique<MiniCar>(Location::INDIA);
            case CarType::LUXURY: return std::make_unique<LuxuryCar>(Location::INDIA);
            default:              return nullptr;
        }
    }
};

class GlobalCarFactory
{
public:
    static std::unique_ptr<Car> buildCar(CarType model)
    {
        switch (model)
        {
            case CarType::MICRO:  return std::make_unique<MicroCar>(Location::DEFAULT);
            case CarType::MINI:   return std::make_unique<MiniCar>(Location::DEFAULT);
            case CarType::LUXURY: return std::make_unique<LuxuryCar>(Location::DEFAULT);
            default:              return nullptr;
        }
    }
};

class USACarFactory
{
public:
    static std::unique_ptr<Car> buildCar(CarType model)
    {
        switch (model)
        {
            case CarType::MICRO:  return std::make_unique<MicroCar>(Location::USA);
            case CarType::MINI:   return std::make_unique<MiniCar>(Location::USA);
            case CarType::LUXURY: return std::make_unique<LuxuryCar>(Location::USA);
            default:              return nullptr;
        }
    }
};

// Centralized Car Production Hub
class CarProductionHub
{
public:
    static std::unique_ptr<Car> buildCar(CarType type)
    {
        Location location = Location::INDIA;  // Changeable location logic

        switch (location)
        {
            case Location::USA:
                return USACarFactory::buildCar(type);
            case Location::INDIA:
                return IndiaCarFactory::buildCar(type);
            default:
                return GlobalCarFactory::buildCar(type);
        }
    }
};

int main()
{
    std::unique_ptr<Car> microCar = CarProductionHub::buildCar(CarType::MICRO);
    std::cout << microCar->getInfo() << "\n\n";

    std::unique_ptr<Car> miniCar = CarProductionHub::buildCar(CarType::MINI);
    std::cout << miniCar->getInfo() << "\n\n";

    std::unique_ptr<Car> luxuryCar = CarProductionHub::buildCar(CarType::LUXURY);
    std::cout << luxuryCar->getInfo() << "\n";

    return 0;
}
