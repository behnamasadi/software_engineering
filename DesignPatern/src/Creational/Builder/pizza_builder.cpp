#include <memory>
#include <iostream>
#include <string>

class Dough
{
    std::string m_name;
public:
    Dough(){}
    Dough(std::string name):m_name(name){}
    std::string desciption()
    {
        return m_name;
    }
};

class Sauce
{
    std::string m_name;
public:
    Sauce(){}
    Sauce(std::string name):m_name(name){}
    std::string desciption()
    {
        return m_name;
    }
};

class Topping
{
    std::string m_name;

public:
    Topping(){}
    Topping(std::string name):m_name(name){}
    std::string desciption()
    {
        return m_name;
    }
};

class Pizza
{
public:
    Dough m_dough;
    Sauce m_sauce;
    Topping m_topping;
    void setDough(Dough dough){m_dough=dough;}
    void setSauce(Sauce sauce){m_sauce=sauce;}
    void setTopping(Topping topping){m_topping=topping;}
    void print()
    {
        std::cout<<m_dough.desciption()<<","<<m_sauce.desciption()<<","<<m_topping.desciption() <<std::endl;
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
        pizza->setDough(Dough("Hawaiian dough"));
    }
    void  buildSauce()override
    {
        pizza->setSauce(Sauce("Hawaiian Sauce"));
    }
    void  buildTopping()override
    {
        pizza->setTopping(Topping("Hawaiian topping"));
    }
};

class SpicyPizzaBuilder:public PizzaBuilder
{
    void  buildDough()override
    {
        pizza->setDough(Dough("Spicy dough"));
    }
    void  buildSauce()override
    {
        pizza->setSauce(Sauce("Spicy Sauce"));
    }
    void  buildTopping()override
    {
        pizza->setTopping(Topping("Spicy topping"));
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
