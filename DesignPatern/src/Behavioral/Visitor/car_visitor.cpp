#include <iostream>
#include <memory>
#include <string>
#include <vector>

// Forward declarations
class VehicleComponentVisitor;
class Chassis;
class Vehicle;
class Motor;
class Wheel;
class Seats;

// Base class for all vehicle components
class VehicleComponent {
public:
  virtual void accept(VehicleComponentVisitor *visitor) = 0;
  virtual ~VehicleComponent() = default;
};

// Visitor interface
class VehicleComponentVisitor {
public:
  virtual void visit(Chassis *chassis) = 0;
  virtual void visit(Vehicle *vehicle) = 0;
  virtual void visit(Motor *motor) = 0;
  virtual void visit(Wheel *wheel) = 0;
  virtual void visit(Seats *seats) = 0;
  virtual ~VehicleComponentVisitor() = default;
};

// Concrete element: Wheel
class Wheel : public VehicleComponent {
private:
  std::string position;

public:
  explicit Wheel(const std::string &pos) : position(pos) {}

  std::string getPosition() const { return position; }

  void accept(VehicleComponentVisitor *visitor) override { visitor->visit(this); }
};

// Concrete element: Chassis
class Chassis : public VehicleComponent {
public:
  void accept(VehicleComponentVisitor *visitor) override { visitor->visit(this); }
};

// Concrete element: Motor
class Motor : public VehicleComponent {
public:
  void accept(VehicleComponentVisitor *visitor) override { visitor->visit(this); }
};

// Concrete element: Seats
class Seats : public VehicleComponent {
public:
  void accept(VehicleComponentVisitor *visitor) override { visitor->visit(this); }
};

// Concrete element: Vehicle (composite structure)
class Vehicle : public VehicleComponent {
private:
  std::vector<std::shared_ptr<VehicleComponent>> components;

public:
  Vehicle() {
    components.emplace_back(std::make_shared<Wheel>("front left"));
    components.emplace_back(std::make_shared<Wheel>("front right"));
    components.emplace_back(std::make_shared<Wheel>("back left"));
    components.emplace_back(std::make_shared<Wheel>("back right"));
    components.emplace_back(std::make_shared<Chassis>());
    components.emplace_back(std::make_shared<Motor>());
    components.emplace_back(std::make_shared<Seats>());
  }

  void accept(VehicleComponentVisitor *visitor) override {
    for (const auto &component : components) {
      component->accept(visitor);
    }
    visitor->visit(this);
  }
};

// Concrete visitor: Performs actions
class VehicleActionVisitor : public VehicleComponentVisitor {
public:
  void visit(Chassis *chassis) override {
    std::cout << "Inspecting the chassis structure" << std::endl;
  }

  void visit(Vehicle *vehicle) override {
    std::cout << "Powering up the vehicle" << std::endl;
  }

  void visit(Wheel *wheel) override {
    std::cout << "Inflating the " << wheel->getPosition() << " wheel" << std::endl;
  }

  void visit(Motor *motor) override {
    std::cout << "Calibrating the motor" << std::endl;
  }

  void visit(Seats *seats) override {
    std::cout << "Adjusting the seats" << std::endl;
  }
};

// Concrete visitor: Prints components
class VehiclePrintVisitor : public VehicleComponentVisitor {
public:
  void visit(Chassis *chassis) override {
    std::cout << "Examining the chassis" << std::endl;
  }

  void visit(Vehicle *vehicle) override {
    std::cout << "Checking the entire vehicle" << std::endl;
  }

  void visit(Wheel *wheel) override {
    std::cout << "Checking " << wheel->getPosition() << " wheel" << std::endl;
  }

  void visit(Motor *motor) override {
    std::cout << "Inspecting the motor" << std::endl;
  }

  void visit(Seats *seats) override {
    std::cout << "Examining the seats" << std::endl;
  }
};

// Main function
int main() {
  auto vehicle = std::make_shared<Vehicle>();

  VehiclePrintVisitor printVisitor;
  VehicleActionVisitor actionVisitor;

  vehicle->accept(&printVisitor);
  vehicle->accept(&actionVisitor);

  return 0;
}
