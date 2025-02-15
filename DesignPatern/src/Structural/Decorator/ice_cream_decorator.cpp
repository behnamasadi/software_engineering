#include <memory>
#include <iostream>
#include <string>

// Base class for Ice Cream
class IceCreamBase
{
public:
    virtual void make() const = 0;
    virtual ~IceCreamBase() = default; // Ensures proper polymorphic destruction
};

// Concrete Ice Cream Base
class BasicIceCream : public IceCreamBase
{
public:
    void make() const override
    {
        std::cout << "\nMilk + Sugar + Ice Cream Base";
    }
};

// Abstract Decorator Class
class IceCreamDecorator : public IceCreamBase
{
protected:
    std::unique_ptr<IceCreamBase> m_decorator;

public:
    explicit IceCreamDecorator(std::unique_ptr<IceCreamBase> decorator)
        : m_decorator(std::move(decorator)) {}

    void make() const override
    {
        m_decorator->make();
    }
};

// Concrete Decorator - Fruit Topping
class FruitTopping : public IceCreamDecorator
{
public:
    explicit FruitTopping(std::unique_ptr<IceCreamBase> decorator)
        : IceCreamDecorator(std::move(decorator)) {}

    void make() const override
    {
        IceCreamDecorator::make();
        std::cout << " + Fresh Fruits";
    }
};

// Concrete Decorator - Nut Topping
class NutTopping : public IceCreamDecorator
{
public:
    explicit NutTopping(std::unique_ptr<IceCreamBase> decorator)
        : IceCreamDecorator(std::move(decorator)) {}

    void make() const override
    {
        IceCreamDecorator::make();
        std::cout << " + Crunchy Nuts";
    }
};

// Concrete Decorator - Wafer Crunch
class WaferCrunch : public IceCreamDecorator
{
public:
    explicit WaferCrunch(std::unique_ptr<IceCreamBase> decorator)
        : IceCreamDecorator(std::move(decorator)) {}

    void make() const override
    {
        IceCreamDecorator::make();
        std::cout << " + Crispy Wafers";
    }
};

int main()
{
    // Start with a basic ice cream
    std::unique_ptr<IceCreamBase> iceCream = std::make_unique<BasicIceCream>();
    iceCream->make();

    std::cout << "\n\nAdding Toppings:\n";
    
    // Add fruit topping
    iceCream = std::make_unique<FruitTopping>(std::move(iceCream));
    iceCream->make();

    // Add nut topping
    iceCream = std::make_unique<NutTopping>(std::move(iceCream));
    iceCream->make();

    // Add wafer topping
    iceCream = std::make_unique<WaferCrunch>(std::move(iceCream));
    iceCream->make();

    return 0;
}
