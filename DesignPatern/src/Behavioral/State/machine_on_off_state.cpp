// State — minimal on/off device.
// The Device delegates turnOn/turnOff to a state object that decides what
// happens. Each state is responsible for driving the next transition.

#include <iostream>
#include <memory>

class Device;

class PowerState {
public:
    virtual ~PowerState() = default;
    virtual void turnOn(Device&)  { std::cout << "  already ON\n"; }
    virtual void turnOff(Device&) { std::cout << "  already OFF\n"; }
    virtual const char* name() const = 0;
};

class On  : public PowerState { public: void turnOff(Device&) override; const char* name() const override { return "ON";  } };
class Off : public PowerState { public: void turnOn (Device&) override; const char* name() const override { return "OFF"; } };

class Device {
public:
    Device() : state_(std::make_unique<Off>()) {
        std::cout << "Device starts " << state_->name() << '\n';
    }

    void setState(std::unique_ptr<PowerState> next) {
        std::cout << "  " << state_->name() << " -> " << next->name() << '\n';
        state_ = std::move(next);
    }

    void turnOn()  { state_->turnOn(*this); }
    void turnOff() { state_->turnOff(*this); }

private:
    std::unique_ptr<PowerState> state_;
};

void On ::turnOff(Device& d) { d.setState(std::make_unique<Off>()); }
void Off::turnOn (Device& d) { d.setState(std::make_unique<On>());  }

int main() {
    Device d;
    d.turnOn();
    d.turnOff();
    d.turnOff();   // no-op
    d.turnOn();
}
