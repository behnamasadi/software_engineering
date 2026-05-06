// Builder — separate the recipe (Director) from the parts (Builder).
//
// Pizza               : the product we're constructing
// PizzaBuilder        : abstract builder; one method per part
// HawaiianPizzaBuilder/SpicyPizzaBuilder : concrete builders
// Cook                : director; runs the same recipe with different builders

#include <iostream>
#include <memory>
#include <string>
#include <utility>

class Pizza {
public:
    void setDough(std::string dough)     { dough_   = std::move(dough); }
    void setSauce(std::string sauce)     { sauce_   = std::move(sauce); }
    void setTopping(std::string topping) { topping_ = std::move(topping); }

    void describe() const {
        std::cout << "  pizza: " << dough_ << " + " << sauce_ << " + " << topping_ << '\n';
    }

private:
    std::string dough_;
    std::string sauce_;
    std::string topping_;
};

class PizzaBuilder {
public:
    virtual ~PizzaBuilder() = default;

    void start() { pizza_ = std::make_unique<Pizza>(); }

    virtual void buildDough()   = 0;
    virtual void buildSauce()   = 0;
    virtual void buildTopping() = 0;

    std::unique_ptr<Pizza> retrieve() { return std::move(pizza_); }

protected:
    std::unique_ptr<Pizza> pizza_;
};

class HawaiianPizzaBuilder : public PizzaBuilder {
public:
    void buildDough()   override { pizza_->setDough("Hawaiian crust"); }
    void buildSauce()   override { pizza_->setSauce("pineapple sauce"); }
    void buildTopping() override { pizza_->setTopping("ham and pineapple"); }
};

class SpicyPizzaBuilder : public PizzaBuilder {
public:
    void buildDough()   override { pizza_->setDough("thin crust"); }
    void buildSauce()   override { pizza_->setSauce("hot chili sauce"); }
    void buildTopping() override { pizza_->setTopping("pepperoni and jalapenos"); }
};

class Cook {
public:
    explicit Cook(std::unique_ptr<PizzaBuilder> builder) : builder_(std::move(builder)) {}

    std::unique_ptr<Pizza> make() {
        builder_->start();
        builder_->buildDough();
        builder_->buildSauce();
        builder_->buildTopping();
        return builder_->retrieve();
    }

private:
    std::unique_ptr<PizzaBuilder> builder_;
};

int main() {
    std::cout << "Spicy:\n";
    Cook spicy(std::make_unique<SpicyPizzaBuilder>());
    spicy.make()->describe();

    std::cout << "Hawaiian:\n";
    Cook hawaiian(std::make_unique<HawaiianPizzaBuilder>());
    hawaiian.make()->describe();
}
