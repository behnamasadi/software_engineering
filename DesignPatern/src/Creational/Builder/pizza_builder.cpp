#include <memory>
#include <iostream>
#include <string>

class Pizza
{
public:
    std::string dough;
    std::string sauce;
    std::string topping;
    void print()
    {
        std::cout<<dough <<","<<sauce<<","<<topping <<std::endl;
    }
};

class PizzaBuilder
{
protected:
    std::unique_ptr<Pizza> pizza;
public:
    virtual void buildDough()=0;
    virtual void buildSauce()=0;
    virtual void buildTopping()=0;
    void createNewPizza()
    {
        pizza = std::make_unique<Pizza>();
    }
    Pizza* getPizza()
    {
        return pizza.release();
    }
};

class HawaiianPizzaBuilder:public PizzaBuilder
{
    void  buildDough()override
    {
        pizza->dough="Hawaiian dough";
    }
    void  buildSauce()override
    {
        pizza->sauce="Hawaiian Sauce";
    }
    void  buildTopping()override
    {
        pizza->topping="Hawaiian topping";
    }
};

class SpicyPizzaBuilder:public PizzaBuilder
{
    void  buildDough()override
    {
        pizza->dough="Spicy dough";
    }
    void  buildSauce()override
    {
        pizza->sauce="Spicy Sauce";
    }
    void  buildTopping()override
    {
        pizza->topping="Spicy topping";
    }

};

class Cook
{
    PizzaBuilder *pizzaBuilder;
public:
    Cook(PizzaBuilder *pizzaBuilder):pizzaBuilder(pizzaBuilder){}
    void createPizza()
    {
        pizzaBuilder->createNewPizza();
        pizzaBuilder->buildDough();
        pizzaBuilder->buildSauce();
        pizzaBuilder->buildTopping();
    }

    void showPizza() const
    {
        pizzaBuilder->getPizza()->print();
    }
};

int main()
{
    //std::unique_ptr<PizzaBuilder> pizzaBuilder_ptr=std::make_unique<SpicyPizzaBuilder>;
    PizzaBuilder *pizzaBuilder_ptr=new SpicyPizzaBuilder;
    Cook cooker(pizzaBuilder_ptr);
    cooker.createPizza();
    cooker.showPizza();

}
