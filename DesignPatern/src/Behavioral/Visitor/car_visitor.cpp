// Visitor — operation that walks a heterogeneous structure (a Car made of
// wheels, body, engine) without modifying the element classes. Each visitor
// (PrintVisitor, DoVisitor) is a new operation; the elements stay untouched.

#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

class Body;
class Engine;
class Wheel;
class Car;

class CarElementVisitor {
public:
    virtual ~CarElementVisitor() = default;
    virtual void visit(const Body& body) = 0;
    virtual void visit(const Engine& engine) = 0;
    virtual void visit(const Wheel& wheel) = 0;
    virtual void visit(const Car& car) = 0;
};

class CarElement {
public:
    virtual ~CarElement() = default;
    virtual void accept(CarElementVisitor& visitor) const = 0;
};

class Wheel : public CarElement {
public:
    explicit Wheel(std::string name) : name_(std::move(name)) {}
    const std::string& name() const { return name_; }
    void accept(CarElementVisitor& visitor) const override { visitor.visit(*this); }
private:
    std::string name_;
};

class Body : public CarElement {
public:
    void accept(CarElementVisitor& visitor) const override { visitor.visit(*this); }
};

class Engine : public CarElement {
public:
    void accept(CarElementVisitor& visitor) const override { visitor.visit(*this); }
};

class Car : public CarElement {
public:
    Car() {
        parts_.push_back(std::make_unique<Wheel>("front-left"));
        parts_.push_back(std::make_unique<Wheel>("front-right"));
        parts_.push_back(std::make_unique<Wheel>("back-left"));
        parts_.push_back(std::make_unique<Wheel>("back-right"));
        parts_.push_back(std::make_unique<Body>());
        parts_.push_back(std::make_unique<Engine>());
    }

    void accept(CarElementVisitor& visitor) const override {
        for (const auto& part : parts_) part->accept(visitor);
        visitor.visit(*this);
    }

private:
    std::vector<std::unique_ptr<CarElement>> parts_;
};

class PrintVisitor : public CarElementVisitor {
public:
    void visit(const Body&)            override { std::cout << "visit body\n"; }
    void visit(const Engine&)          override { std::cout << "visit engine\n"; }
    void visit(const Wheel& wheel)     override { std::cout << "visit " << wheel.name() << " wheel\n"; }
    void visit(const Car&)             override { std::cout << "visit car\n"; }
};

class DoVisitor : public CarElementVisitor {
public:
    void visit(const Body&)            override { std::cout << "moving body\n"; }
    void visit(const Engine&)          override { std::cout << "starting engine\n"; }
    void visit(const Wheel& wheel)     override { std::cout << "kicking " << wheel.name() << " wheel\n"; }
    void visit(const Car&)             override { std::cout << "starting car\n"; }
};

int main() {
    Car car;
    PrintVisitor printer;
    DoVisitor doer;

    std::cout << "--- print ---\n";
    car.accept(printer);
    std::cout << "--- do ---\n";
    car.accept(doer);
}
