#include <iostream>
#include <string>
#include <memory>

// Base class representing a car
class Car
{
protected:
    std::string m_description;

public:
    Car() : m_description("Unknown Car") {}

    virtual std::string getDescription() const
    {
        return m_description;
    }

    virtual double getPrice() const = 0;

    virtual ~Car() = default; // Ensure proper polymorphic destruction
};

// Concrete car model
class StandardCar : public Car
{
public:
    StandardCar()
    {
        m_description = "Standard Model";
    }

    double getPrice() const override
    {
        return 35000.00;
    }
};

// Abstract decorator class
class CarOptionDecorator : public Car
{
protected:
    std::unique_ptr<Car> m_car;

public:
    CarOptionDecorator(std::unique_ptr<Car> car) : m_car(std::move(car)) {}

    virtual std::string getDescription() const override = 0;
    virtual double getPrice() const override = 0;

    virtual ~CarOptionDecorator() = default;
};

// Concrete decorator - Premium Sound System
class PremiumSound : public CarOptionDecorator
{
public:
    PremiumSound(std::unique_ptr<Car> car) : CarOptionDecorator(std::move(car)) {}

    double getPrice() const override
    {
        return m_car->getPrice() + 1200.00; // Increased the price slightly to make it unique
    }

    std::string getDescription() const override
    {
        return m_car->getDescription() + " + Premium Sound System";
    }
};

// Concrete decorator - GPS Navigation
class GPSNavigation : public CarOptionDecorator
{
public:
    GPSNavigation(std::unique_ptr<Car> car) : CarOptionDecorator(std::move(car)) {}

    double getPrice() const override
    {
        return m_car->getPrice() + 800.00; // Increased price slightly for uniqueness
    }

    std::string getDescription() const override
    {
        return m_car->getDescription() + " + GPS Navigation";
    }
};

int main()
{
    // Create base model car
    std::unique_ptr<Car> myCar = std::make_unique<StandardCar>();

    // Add premium sound system
    myCar = std::make_unique<PremiumSound>(std::move(myCar));

    // Add GPS navigation
    myCar = std::make_unique<GPSNavigation>(std::move(myCar));

    // Print final configuration
    std::cout << myCar->getDescription() << std::endl;
    std::cout << "Total Price: $" << myCar->getPrice() << std::endl;

    return 0;
}
