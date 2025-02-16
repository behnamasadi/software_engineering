#include <iostream>
#include <vector>
#include <string>
#include <memory>

// Visitor Interface using Templates
class CarElementVisitor {
public:
    virtual ~CarElementVisitor() = default;

    // Now the visit method takes a reference rather than a pointer.
    // It then calls acceptImpl, which must be public in the element classes.
    template <typename T>
    void visit(T &element) {
        element.acceptImpl(*this);
    }
};

// CarElement Interface
class CarElement {
public:
    virtual ~CarElement() = default;

    // Accept by reference
    virtual void accept(CarElementVisitor &visitor) = 0;

    // We'll override acceptImpl as public in the concrete classes
    // so that CarElementVisitor can call it.
    virtual void acceptImpl(CarElementVisitor &visitor) = 0;
};

// Concrete Elements
class Wheel : public CarElement {
private:
    std::string name;

public:
    Wheel(const std::string &name) : name(name) {}

    std::string getName() const { return name; }

    // Accept by reference
    void accept(CarElementVisitor &visitor) override {
        // Pass the *this reference to the visitor
        visitor.visit(*this);
    }

    // Make acceptImpl public
    void acceptImpl(CarElementVisitor &visitor) override {
        std::cout << "Visiting wheel: " << name << std::endl;
    }
};

class Body : public CarElement {
public:
    void accept(CarElementVisitor &visitor) override {
        visitor.visit(*this);
    }

    // Make acceptImpl public
    void acceptImpl(CarElementVisitor &visitor) override {
        std::cout << "Visiting body" << std::endl;
    }
};

class Engine : public CarElement {
public:
    void accept(CarElementVisitor &visitor) override {
        visitor.visit(*this);
    }

    // Make acceptImpl public
    void acceptImpl(CarElementVisitor &visitor) override {
        std::cout << "Visiting engine" << std::endl;
    }
};

class Car : public CarElement {
private:
    std::vector<std::unique_ptr<CarElement>> elements;

public:
    // Use unique_ptr to own your CarElements
    Car() {
        elements.emplace_back(std::make_unique<Wheel>("front left"));
        elements.emplace_back(std::make_unique<Wheel>("front right"));
        elements.emplace_back(std::make_unique<Wheel>("back left"));
        elements.emplace_back(std::make_unique<Wheel>("back right"));
        elements.emplace_back(std::make_unique<Body>());
        elements.emplace_back(std::make_unique<Engine>());
    }

    void accept(CarElementVisitor &visitor) override {
        // Accept the visitor for each contained element
        for (auto &element : elements) {
            element->accept(visitor);
        }
        // Finally, visit the "Car" itself
        visitor.visit(*this);
    }

    // Make acceptImpl public
    void acceptImpl(CarElementVisitor &visitor) override {
        std::cout << "Visiting car" << std::endl;
    }
};

// Main function
int main() {
    Car car;
    CarElementVisitor visitor;

    std::cout << "\n--- Visiting elements ---" << std::endl;
    car.accept(visitor);

    return 0;
}
