#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

// Forward declaration
class Airplane;

// Mediator Interface
class IMediator {
public:
  virtual void notify(Airplane *sender, const std::string &event) = 0;
  virtual ~IMediator() = default;
};

// Colleague class (Airplane)
class Airplane {
private:
  std::string name;
  IMediator *mediator;

public:
  Airplane(std::string name, IMediator *mediator)
      : name(name), mediator(mediator) {}

  void requestLanding() {
    std::cout << name << " requests landing.\n";
    mediator->notify(this, "LandingRequest");
  }

  void requestTakeoff() {
    std::cout << name << " requests takeoff.\n";
    mediator->notify(this, "TakeoffRequest");
  }

  void land() { std::cout << name << " has landed successfully.\n"; }

  void takeoff() { std::cout << name << " has taken off successfully.\n"; }

  std::string getName() const { return name; }
};

// Concrete Mediator (ATC Tower)
class ATCTower : public IMediator {
private:
  std::vector<Airplane *> airplanesInAir;
  std::vector<Airplane *> airplanesOnGround;

public:
  void registerAirplane(Airplane *airplane, bool isInAir) {
    if (isInAir)
      airplanesInAir.push_back(airplane);
    else
      airplanesOnGround.push_back(airplane);
  }

  void notify(Airplane *sender, const std::string &event) override {
    if (event == "LandingRequest") {
      if (airplanesOnGround.empty()) {
        std::cout << "ATC: " << sender->getName() << " is cleared to land.\n";
        sender->land();
        moveAirplane(sender, airplanesInAir, airplanesOnGround);
      } else {
        std::cout << "ATC: " << sender->getName()
                  << " must hold, runway is occupied.\n";
      }
    } else if (event == "TakeoffRequest") {
      if (!airplanesOnGround.empty()) {
        std::cout << "ATC: " << sender->getName()
                  << " is cleared for takeoff.\n";
        sender->takeoff();
        moveAirplane(sender, airplanesOnGround, airplanesInAir);
      } else {
        std::cout << "ATC: No airplanes on the ground to take off.\n";
      }
    }
  }

private:
  void moveAirplane(Airplane *airplane, std::vector<Airplane *> &from,
                    std::vector<Airplane *> &to) {
    auto it = std::find(from.begin(), from.end(), airplane);
    if (it != from.end()) {
      from.erase(it);
      to.push_back(airplane);
    }
  }
};

// Client Code
int main() {
  ATCTower atc;

  Airplane plane1("Flight A123", &atc);
  Airplane plane2("Flight B456", &atc);
  Airplane plane3("Flight C789", &atc);

  atc.registerAirplane(&plane1, true);
  atc.registerAirplane(&plane2, true);
  atc.registerAirplane(&plane3, false);

  plane1.requestLanding();
  plane2.requestLanding();
  plane3.requestTakeoff();

  return 0;
}
