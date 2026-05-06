// Command — encapsulate a request as an object so callers can be parameterized,
// queued, logged, or undone.
//
// Roles: Command (interface), Receiver (Light), ConcreteCommand (LightOn/Off),
// Invoker (RemoteControl), Client (main).

#include <iostream>
#include <memory>
#include <utility>

class Light {
public:
    void turnOn()  { std::cout << "[Light] ON\n"; }
    void turnOff() { std::cout << "[Light] OFF\n"; }
};

class Command {
public:
    virtual ~Command() = default;
    virtual void execute() = 0;
};

class LightOnCommand : public Command {
public:
    explicit LightOnCommand(Light& light) : light_(light) {}
    void execute() override { light_.turnOn(); }
private:
    Light& light_;
};

class LightOffCommand : public Command {
public:
    explicit LightOffCommand(Light& light) : light_(light) {}
    void execute() override { light_.turnOff(); }
private:
    Light& light_;
};

class RemoteControl {
public:
    void setCommand(std::unique_ptr<Command> cmd) { cmd_ = std::move(cmd); }
    void pressButton() {
        if (cmd_) cmd_->execute();
        else std::cout << "[Remote] no command set\n";
    }
private:
    std::unique_ptr<Command> cmd_;
};

int main() {
    Light light;
    RemoteControl remote;

    remote.setCommand(std::make_unique<LightOnCommand>(light));
    remote.pressButton();

    remote.setCommand(std::make_unique<LightOffCommand>(light));
    remote.pressButton();
}
