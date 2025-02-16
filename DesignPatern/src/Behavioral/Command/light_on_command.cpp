#include <iostream>
#include <memory>



// Command Interface
class Command {
public:
    virtual void execute() = 0;
    virtual ~Command() = default; // Virtual destructor to ensure proper cleanup
};

// Receiver Class
class Light {
public:
    void turnOn() { std::cout << "[Light] Turning ON\n"; }
    void turnOff() { std::cout << "[Light] Turning OFF\n"; }
};

// Command for turning on the light
class LightOnCommand : public Command {
public:
    explicit LightOnCommand(std::shared_ptr<Light> light) : mLight(move(light)) {}
    void execute() override { mLight->turnOn(); }

private:
    std::shared_ptr<Light> mLight;
};

// Command for turning off the light
class LightOffCommand : public Command {
public:
    explicit LightOffCommand(std::shared_ptr<Light> light) : mLight(move(light)) {}
    void execute() override { mLight->turnOff(); }

private:
    std::shared_ptr<Light> mLight;
};

// Toggle command for demonstration
class LightToggleCommand : public Command {
public:
    explicit LightToggleCommand(std::shared_ptr<Light> light) : mLight(move(light)), isOn(false) {}
    void execute() override {
        if (isOn) {
            mLight->turnOff();
        } else {
            mLight->turnOn();
        }
        isOn = !isOn;
    }

private:
    std::shared_ptr<Light> mLight;
    bool isOn;
};

// Invoker (Stores the ConcreteCommand object)
class RemoteControl {
public:
    void setCommand(std::shared_ptr<Command> cmd) { mCmd = move(cmd); }
    void pressButton() {
        if (auto cmd = mCmd.lock()) { // Prevents dangling access
            cmd->execute();
        } else {
            std::cout << "[RemoteControl] No command set!\n";
        }
    }

private:
    std::weak_ptr<Command> mCmd; // Using weak_ptr to avoid unnecessary ownership
};

// The client
int main() {
    // Receiver
    auto light = std::make_shared<Light>();

    // Concrete Command objects
    auto lightOn = std::make_shared<LightOnCommand>(light);
    auto lightOff = std::make_shared<LightOffCommand>(light);
    auto lightToggle = std::make_shared<LightToggleCommand>(light);

    // Invoker object
    RemoteControl control;

    // Execute
    control.setCommand(lightOn);
    control.pressButton();

    control.setCommand(lightOff);
    control.pressButton();

    control.setCommand(lightToggle);
    control.pressButton();
    control.pressButton(); // Toggling back

    return 0; // Smart pointers handle cleanup automatically
}
