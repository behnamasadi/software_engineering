// Observer — RAII variant.
// Each Observer attaches to its subject in the constructor and detaches in
// the destructor. Lifetimes are stack-bound; no smart pointers needed.

#include <algorithm>
#include <iostream>
#include <vector>

class Car;

class Observer {
public:
    explicit Observer(Car& subject);
    virtual ~Observer();

    Observer(const Observer&) = delete;
    Observer& operator=(const Observer&) = delete;

    virtual void onUpdate(const Car& car) = 0;

protected:
    Car& subject_;
};

class Car {
public:
    void attach(Observer& o) { observers_.push_back(&o); }
    void detach(Observer& o) {
        observers_.erase(std::remove(observers_.begin(), observers_.end(), &o),
                         observers_.end());
    }

    double speed() const       { return speed_; }
    double temperature() const { return temperature_; }

    void setSpeed(double s)       { if (s != speed_)       { speed_ = s; notify(); } }
    void setTemperature(double t) { if (t != temperature_) { temperature_ = t; notify(); } }

private:
    void notify() { for (auto* o : observers_) o->onUpdate(*this); }

    std::vector<Observer*> observers_;
    double speed_ = 0;
    double temperature_ = 0;
};

Observer::Observer(Car& subject) : subject_(subject) { subject_.attach(*this); }
Observer::~Observer() { subject_.detach(*this); }

class Speedometer : public Observer {
public:
    using Observer::Observer;
    void onUpdate(const Car& car) override {
        std::cout << "[speed]  " << car.speed() << " km/h\n";
    }
};

class Thermometer : public Observer {
public:
    using Observer::Observer;
    void onUpdate(const Car& car) override {
        std::cout << "[temp]   " << car.temperature() << " C\n";
    }
};

int main() {
    Car car;
    Speedometer speed(car);
    Thermometer temp(car);

    car.setSpeed(60);
    car.setTemperature(-2);
    car.setSpeed(60);   // no change → no notification
    car.setSpeed(80);
}
