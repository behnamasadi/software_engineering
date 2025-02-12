#include <iostream>
#include <memory>

class Device;  // Forward declaration

class PowerState {
public:
    virtual ~PowerState() = default;
    virtual void turnOn(Device *device) {
        std::cout << "   Already ON\n";
    }
    virtual void turnOff(Device *device) {
        std::cout << "   Already OFF\n";
    }
    virtual std::string getName() const = 0;
};

class ActiveState : public PowerState {
public:
    void turnOff(Device *device) override;
    std::string getName() const override { return "ON"; }
};

class InactiveState : public PowerState {
public:
    void turnOn(Device *device) override;
    std::string getName() const override { return "OFF"; }
};

class Device {
private:
    std::unique_ptr<PowerState> currentState;

public:
    Device() : currentState(std::make_unique<InactiveState>()) {
        std::cout << "Device initialized in state: " << currentState->getName() << "\n";
    }

    void setCurrent(std::unique_ptr<PowerState> newState) {
        std::cout << "   Switching state from " << currentState->getName() 
                  << " to " << newState->getName() << "\n";
        currentState = std::move(newState);
    }

    void turnOn() {
        currentState->turnOn(this);
    }

    void turnOff() {
        currentState->turnOff(this);
    }
};

void ActiveState::turnOff(Device *device) {
    std::cout << "   Turning OFF...\n";
    device->setCurrent(std::make_unique<InactiveState>());
}

void InactiveState::turnOn(Device *device) {
    std::cout << "   Turning ON...\n";
    device->setCurrent(std::make_unique<ActiveState>());
}

int main() {
    Device device;
    
    device.turnOn();
    device.turnOff();
    device.turnOff();  // No state change should occur
    device.turnOn();
    
    return 0;
}
