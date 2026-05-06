// Command — generic template variant.
// A single GenericCommand<Receiver> binds any (receiver, action) pair without
// needing a separate ConcreteCommand class per action.

#include <functional>
#include <iostream>
#include <memory>
#include <utility>

class Command {
public:
    virtual ~Command() = default;
    virtual void execute() = 0;
};

template <typename Receiver>
class GenericCommand : public Command {
public:
    using Action = std::function<void(Receiver&)>;

    GenericCommand(Receiver& receiver, Action action)
        : receiver_(receiver), action_(std::move(action)) {}

    void execute() override { action_(receiver_); }

private:
    Receiver& receiver_;
    Action action_;
};

class Light {
public:
    void turnOn()  { std::cout << "[Light] ON\n"; }
    void turnOff() { std::cout << "[Light] OFF\n"; }
};

int main() {
    Light light;

    std::unique_ptr<Command> on  =
        std::make_unique<GenericCommand<Light>>(light, &Light::turnOn);
    std::unique_ptr<Command> off =
        std::make_unique<GenericCommand<Light>>(light, &Light::turnOff);

    on->execute();
    off->execute();
}
