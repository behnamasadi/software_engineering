#include <iostream>
#include <memory>
#include <string>
#include <vector>

/*
 * The following example demonstrates the Visitor pattern.
 * A tree structure (a car with components like wheels, body, and engine)
 * is traversed by different visitors, performing distinct operations.
 */

// Forward declarations
class CarElementVisitor;
class Body;
class Car;
class Engine;
class Wheel;

// Base class for all car elements
class CarElement {
public:
  virtual void accept(CarElementVisitor *visitor) = 0; // Pure virtual function
  virtual ~CarElement() = default; // Virtual destructor for proper cleanup
};

// Visitor interface
class CarElementVisitor {
public:
  virtual void visit(Body *body) = 0;
  virtual void visit(Car *car) = 0;
  virtual void visit(Engine *engine) = 0;
  virtual void visit(Wheel *wheel) = 0;
  virtual ~CarElementVisitor() = default;
};

// Concrete element: Wheel
class Wheel : public CarElement {
private:
  std::string name;

public:
  explicit Wheel(const std::string &name) : name(name) {}

  std::string getName() const { return name; }

  void accept(CarElementVisitor *visitor) override { visitor->visit(this); }
};

// Concrete element: Body
class Body : public CarElement {
public:
  void accept(CarElementVisitor *visitor) override { visitor->visit(this); }
};

// Concrete element: Engine
class Engine : public CarElement {
public:
  void accept(CarElementVisitor *visitor) override { visitor->visit(this); }
};

// Concrete element: Car (composite structure)
class Car : public CarElement {
private:
  std::vector<std::unique_ptr<CarElement>> elements;

public:
  Car() {
    elements.emplace_back(std::make_unique<Wheel>("front left"));
    elements.emplace_back(std::make_unique<Wheel>("front right"));
    elements.emplace_back(std::make_unique<Wheel>("back left"));
    elements.emplace_back(std::make_unique<Wheel>("back right"));
    elements.emplace_back(std::make_unique<Body>());
    elements.emplace_back(std::make_unique<Engine>());
  }

  void accept(CarElementVisitor *visitor) override {
    for (const auto &element : elements) {
      element->accept(visitor);
    }
    visitor->visit(this);
  }
};

// Concrete visitor: Performs actions
class CarElementDoVisitor : public CarElementVisitor {
public:
  void visit(Body *body) override {
    std::cout << "Moving my body" << std::endl;
  }

  void visit(Car *car) override { std::cout << "Starting my car" << std::endl; }

  void visit(Wheel *wheel) override {
    std::cout << "Kicking my " << wheel->getName() << " wheel" << std::endl;
  }

  void visit(Engine *engine) override {
    std::cout << "Starting my engine" << std::endl;
  }
};

// Concrete visitor: Prints elements
class CarElementPrintVisitor : public CarElementVisitor {
public:
  void visit(Body *body) override { std::cout << "Visiting body" << std::endl; }

  void visit(Car *car) override { std::cout << "Visiting car" << std::endl; }

  void visit(Engine *engine) override {
    std::cout << "Visiting engine" << std::endl;
  }

  void visit(Wheel *wheel) override {
    std::cout << "Visiting " << wheel->getName() << " wheel" << std::endl;
  }
};

// Main function
int main() {
  auto car = std::make_unique<Car>(); // Use smart pointer for safety

  CarElementPrintVisitor printVisitor;
  CarElementDoVisitor doVisitor;

  car->accept(&printVisitor);
  car->accept(&doVisitor);

  return 0; // No memory leaks
}
