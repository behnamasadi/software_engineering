#include <iostream>
#include <unordered_map>
#include <memory>
#include <string>

using namespace std;

// Prototype Design Pattern
// Intent: Lets you copy existing objects without making your code dependent on their classes.

enum class Type {
    PROTOTYPE_1,
    PROTOTYPE_2
};

class Prototype {
protected:
    string prototype_name_;
    float prototype_field_{};

public:
    Prototype(string prototype_name) : prototype_name_(std::move(prototype_name)) {}
    virtual ~Prototype() = default;
    virtual std::unique_ptr<Prototype> Clone() const = 0;
    virtual void Method(float prototype_field) {
        prototype_field_ = prototype_field;
        std::cout << "Call Method from " << prototype_name_ << " with field: " << prototype_field_ << std::endl;
    }
};

class ConcretePrototype1 : public Prototype {
private:
    float concrete_prototype_field1_{};

public:
    ConcretePrototype1(string prototype_name, float concrete_prototype_field)
        : Prototype(std::move(prototype_name)), concrete_prototype_field1_(concrete_prototype_field) {}

    std::unique_ptr<Prototype> Clone() const override {
        return std::make_unique<ConcretePrototype1>(*this);
    }
};

class ConcretePrototype2 : public Prototype {
private:
    float concrete_prototype_field2_{};

public:
    ConcretePrototype2(string prototype_name, float concrete_prototype_field)
        : Prototype(std::move(prototype_name)), concrete_prototype_field2_(concrete_prototype_field) {}

    std::unique_ptr<Prototype> Clone() const override {
        return std::make_unique<ConcretePrototype2>(*this);
    }
};

class PrototypeFactory {
private:
    std::unordered_map<Type, std::unique_ptr<Prototype>> prototypes_;

public:
    PrototypeFactory() {
        prototypes_[Type::PROTOTYPE_1] = std::make_unique<ConcretePrototype1>("PROTOTYPE_1", 50.f);
        prototypes_[Type::PROTOTYPE_2] = std::make_unique<ConcretePrototype2>("PROTOTYPE_2", 60.f);
    }

    std::unique_ptr<Prototype> CreatePrototype(Type type) {
        return prototypes_[type]->Clone();
    }
};

void Client(PrototypeFactory &prototype_factory) {
    std::cout << "Let's create a Prototype 1\n";
    auto prototype = prototype_factory.CreatePrototype(Type::PROTOTYPE_1);
    prototype->Method(90);

    std::cout << "\nLet's create a Prototype 2\n";
    prototype = prototype_factory.CreatePrototype(Type::PROTOTYPE_2);
    prototype->Method(10);
}

int main() {
    PrototypeFactory prototype_factory;
    Client(prototype_factory);
    return 0;
}