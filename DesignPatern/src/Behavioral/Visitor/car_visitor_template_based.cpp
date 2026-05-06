// Visitor — template-based variant.
// Instead of a Visitor *interface* with one overload per element type, we
// hold a callable (lambda, function-object) that has a templated operator().
// Adding a new element type doesn't require touching the visitor base class;
// the callable just has to handle it.

#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

// Type-erased visitor: stores any object whose operator() accepts each
// element type we'll dispatch to.
class CarElement;
class Body;
class Engine;
class Wheel;
class Car;

class CarElementVisitor {
public:
    virtual ~CarElementVisitor() = default;
    virtual void operator()(const Body& body) = 0;
    virtual void operator()(const Engine& engine) = 0;
    virtual void operator()(const Wheel& wheel) = 0;
    virtual void operator()(const Car& car) = 0;
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
    void accept(CarElementVisitor& visitor) const override { visitor(*this); }
private:
    std::string name_;
};

class Body : public CarElement {
public:
    void accept(CarElementVisitor& visitor) const override { visitor(*this); }
};

class Engine : public CarElement {
public:
    void accept(CarElementVisitor& visitor) const override { visitor(*this); }
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
        visitor(*this);
    }
private:
    std::vector<std::unique_ptr<CarElement>> parts_;
};

// Adapter: turn any callable F (with overloaded operator() for each type)
// into a CarElementVisitor. The overloads in F are picked up via templates.
template <typename F>
class LambdaVisitor : public CarElementVisitor {
public:
    explicit LambdaVisitor(F fn) : fn_(std::move(fn)) {}
    void operator()(const Body& body)     override { fn_(body); }
    void operator()(const Engine& engine) override { fn_(engine); }
    void operator()(const Wheel& wheel)   override { fn_(wheel); }
    void operator()(const Car& car)       override { fn_(car); }
private:
    F fn_;
};

// Helper so callers don't have to spell the type out.
template <typename F>
LambdaVisitor<F> makeVisitor(F fn) { return LambdaVisitor<F>(std::move(fn)); }

// A callable with overloaded operator() per element type.
struct PrintAction {
    void operator()(const Body&)        const { std::cout << "visit body\n"; }
    void operator()(const Engine&)      const { std::cout << "visit engine\n"; }
    void operator()(const Wheel& wheel) const { std::cout << "visit " << wheel.name() << " wheel\n"; }
    void operator()(const Car&)         const { std::cout << "visit car\n"; }
};

int main() {
    Car car;
    auto printer = makeVisitor(PrintAction{});
    car.accept(printer);
}
