// Observer — subject keeps a list of observers and notifies them on change.
//
// This variant uses weak_ptr so the subject doesn't extend observer lifetime,
// and dead observers are pruned during notify().

#include <algorithm>
#include <iostream>
#include <memory>
#include <vector>

class Observer {
public:
    virtual ~Observer() = default;
    virtual void onUpdate() = 0;
};

class WeatherStation {
public:
    void subscribe(std::shared_ptr<Observer> obs) {
        observers_.push_back(std::move(obs));
    }

    void setTemperature(int t) {
        temperature_ = t;
        notify();
    }

    int temperature() const { return temperature_; }

private:
    void notify() {
        // Skip + prune any observers that have been destroyed.
        auto last = std::remove_if(observers_.begin(), observers_.end(),
            [](const std::weak_ptr<Observer>& w) { return w.expired(); });
        observers_.erase(last, observers_.end());

        for (auto& w : observers_) {
            if (auto o = w.lock()) o->onUpdate();
        }
    }

    std::vector<std::weak_ptr<Observer>> observers_;
    int temperature_ = 25;
};

class PhoneDisplay : public Observer {
public:
    explicit PhoneDisplay(WeatherStation& s) : station_(s) {}
    void onUpdate() override {
        std::cout << "[Phone]  " << station_.temperature() << "C\n";
    }
private:
    WeatherStation& station_;
};

class WindowDisplay : public Observer {
public:
    explicit WindowDisplay(WeatherStation& s) : station_(s) {}
    void onUpdate() override {
        std::cout << "[Window] " << station_.temperature() << "C\n";
    }
private:
    WeatherStation& station_;
};

int main() {
    WeatherStation station;
    auto phone  = std::make_shared<PhoneDisplay>(station);
    auto window = std::make_shared<WindowDisplay>(station);

    station.subscribe(phone);
    station.subscribe(window);
    station.setTemperature(30);

    phone.reset();              // observer goes away — auto-pruned next notify
    station.setTemperature(35);
}
