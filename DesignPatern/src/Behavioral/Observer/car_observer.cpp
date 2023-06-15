
#include <cmath>
#include <functional>
#include <iostream>
#include <list>

class Car; // Forward declaration for usage in Observer

class Observer {
public:
  explicit Observer(Car &subj);
  virtual ~Observer();

  Observer(const Observer &) = delete; // rule of three
  Observer &operator=(const Observer &) = delete;

  virtual void update(Car &car) const = 0;

private:
  // Reference to a Car object to detach in the destructor
  Car &subject;
};

// Car is the base class for event generation
class Car {
private:
  double m_speed = NAN;
  double m_temperature = NAN;

public:
  using RefObserver = std::reference_wrapper<const Observer>;

  // Notify all the attached observers
  void notify() {
    for (const auto &x : observers) {
      x.get().update(*this);
    }
  }

  double getSpeed() { return m_speed; }
  void setSpeed(double speed) {
    m_speed = speed;
    notify();
  }

  double getTemperature() { return m_temperature; }
  void setTemperature(double temperature) {
    m_temperature = temperature;
    notify();
  }

  // Add an observer
  void attach(const Observer &observer) { observers.push_front(observer); }

  // Remove an observer
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

  // Get notification
  void update(Car &) const override {
    std::cout << "Got a notification" << std::endl;
  }
};

class TemperatureObserver : public Observer {
public:
  TemperatureObserver(Car &subj) : Observer(subj) {}

  void update(Car &car) const override {
    std::cout << "Car Temperature is: " << car.getTemperature() << std::endl;
  }
};
class SpeedObserver : public Observer {
public:
  SpeedObserver(Car &subj) : Observer(subj) {}

  void update(Car &car) const override {
    std::cout << "Car Speed is: " << car.getSpeed() << std::endl;
  }
};

int main() {
  Car car;
  SpeedObserver speedObserver1(car);
  TemperatureObserver temperatureObserver1(car);
  car.setSpeed(20);
  car.setTemperature(-2);
}