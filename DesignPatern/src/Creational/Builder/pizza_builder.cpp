#include <memory>
#include <iostream>
#include <string>

// Dough class
class Dough
{
    std::string m_name;
public:
    explicit Dough(std::string name = "Unknown Dough") : m_name(std::move(name)) {}
    std::string description() const { return m_name; }
};

// Sauce class
class Sauce
{
    std::string m_name;
public:
    explicit Sauce(std::string name = "Unknown Sauce") : m_name(std::move(name)) {}
    std::string description() const { return m_name; }
};

// Topping class
class Topping
{
    std::string m_name;
public:
    explicit Topping(std::string name = "Unknown Topping") : m_name(std::move(name)) {}
    std::string description() const { return m_name; }
};

// Pizza class
class Pizza
{
    Dough m_dough;
    Sauce m_sauce;
    Topping m_topping;

public:
    void setDough(const Dough& dough) { m_dough = dough; }
    void setSauce(const Sauce& sauce) { m_sauce = sauce; }
    void setTopping(const Topping& topping) { m_topping = topping; }

    void displayPizza() const
    {
        std::cout << "🍕 Pizza with " << m_dough.description()
                  << ", " << m_sauce.description()
                  << ", and " << m_topping.description() << ".\n";
    }
};

// Abstract Builder
class PizzaBuilder
{
protected:
    std::unique_ptr<Pizza> pizza;

public:
    virtual ~PizzaBuilder() = default;

    void preparePizza()
    {
        pizza = std::make_unique<Pizza>();
    }

    virtual void buildDough() = 0;
    virtual void buildSauce() = 0;
    virtual void buildTopping() = 0;

    std::unique_ptr<Pizza> retrievePizza()
    {
        return std::move(pizza);
    }
};

// Concrete Builder: Hawaiian Pizza
class HawaiianPizzaBuilder : public PizzaBuilder
{
public:
    void buildDough() override
    {
        pizza->setDough(Dough("Hawaiian crust"));
    }

    void buildSauce() override
    {
        pizza->setSauce(Sauce("Sweet pineapple sauce"));
    }

    void buildTopping() override
    {
        pizza->setTopping(Topping("Ham and pineapple"));
    }
};

// Concrete Builder: Spicy Pizza
class SpicyPizzaBuilder : public PizzaBuilder
{
public:
    void buildDough() override
    {
        pizza->setDough(Dough("Spicy thin crust"));
    }

    void buildSauce() override
    {
        pizza->setSauce(Sauce("Hot chili sauce"));
    }

    void buildTopping() override
    {
        pizza->setTopping(Topping("Pepperoni and jalapeños"));
    }
};

// Director class
class Cook
{
private:
    std::unique_ptr<PizzaBuilder> pizzaBuilder;

public:
    explicit Cook(std::unique_ptr<PizzaBuilder> builder) : pizzaBuilder(std::move(builder)) {}

    std::unique_ptr<Pizza> createPizza()
    {
        pizzaBuilder->preparePizza();
        pizzaBuilder->buildDough();
        pizzaBuilder->buildSauce();
        pizzaBuilder->buildTopping();
        return pizzaBuilder->retrievePizza();
    }
};

// Main function
int main()
{
    std::cout << "👨‍🍳 Making a Spicy Pizza:\n";
    std::unique_ptr<PizzaBuilder> spicyBuilder = std::make_unique<SpicyPizzaBuilder>();
    Cook spicyCook(std::move(spicyBuilder));
    std::unique_ptr<Pizza> spicyPizza = spicyCook.createPizza();
    spicyPizza->displayPizza();

    std::cout << "\n👨‍🍳 Making a Hawaiian Pizza:\n";
    std::unique_ptr<PizzaBuilder> hawaiianBuilder = std::make_unique<HawaiianPizzaBuilder>();
    Cook hawaiianCook(std::move(hawaiianBuilder));
    std::unique_ptr<Pizza> hawaiianPizza = hawaiianCook.createPizza();
    hawaiianPizza->displayPizza();

    return 0;
}
