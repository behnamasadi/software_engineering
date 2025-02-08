#include <cmath>
#include <functional>
#include <iostream>
#include <list>

class Car; // Forward declaration for usage in Observer

class Observer {
public:
  explicit Observer(Car &subj);
  virtual ~Observer();

  Observer(const Observer &) = delete; // Rule of Three
  Observer &operator=(const Observer &) = delete;

  virtual void update(Car &car) = 0; // Removed `const` to allow modification

protected:
  Car &subject; // Made protected so derived classes can access it
};

// Car is the base class for event generation
class Car {
private:
  double m_speed = NAN;
  double m_temperature = NAN;

public:
  using RefObserver =
      std::reference_wrapper<Observer>; // Allow mutable observers

  ~Car() { observers.clear(); } // Ensure proper cleanup

  // Notify all attached observers
  void notify() {
    for (auto &obs : observers) {
      obs.get().update(*this);
    }
  }

  double getSpeed() const { return m_speed; } // Marked as const
  void setSpeed(double speed) {
    if (m_speed != speed) { // Prevent unnecessary notifications
      m_speed = speed;
      notify();
    }
  }

  double getTemperature() const { return m_temperature; } // Marked as const
  void setTemperature(double temperature) {
    if (m_temperature != temperature) { // Prevent unnecessary notifications
      m_temperature = temperature;
      notify();
    }
  }

  // Add an observer if it’s not already in the list
  void attach(Observer &observer) {
    for (const auto &obs : observers) {
      if (&obs.get() == &observer)
        return; // Already attached
    }
    observers.push_front(observer);
  }

  // Remove an observer safely
  void detach(Observer &observer) {
    observers.remove_if([&observer](const RefObserver &obj) {
      return &obj.get() == &observer;
    });
  }

private:
  std::list<RefObserver> observers;
};

Observer::Observer(Car &subj) : subject(subj) { subject.attach(*this); }

Observer::~Observer() { subject.detach(*this); }

// Example of usage
class ConcreteObserver : public Observer {
public:
  ConcreteObserver(Car &subj) : Observer(subj) {}

  void update(Car &) override {
    std::cout << "Got a notification" << std::endl;
  }
};

// Thermometer
class TemperatureObserver : public Observer {
public:
  TemperatureObserver(Car &subj) : Observer(subj) {}

  void update(Car &car) override {
    std::cout << "Car Temperature is: " << car.getTemperature() << std::endl;
  }
};

// Odometer
class SpeedObserver : public Observer {
public:
  SpeedObserver(Car &subj) : Observer(subj) {}

  void update(Car &car) override {
    std::cout << "Car Speed is: " << car.getSpeed() << std::endl;
  }
};

int main() {
  Car car;
  SpeedObserver speedObserver1(car);
  TemperatureObserver temperatureObserver1(car);

  car.setSpeed(20);
  car.setTemperature(-2);

  return 0; // Ensures proper cleanup
}
