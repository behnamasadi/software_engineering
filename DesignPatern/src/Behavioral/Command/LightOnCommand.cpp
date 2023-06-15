// https://www.bogotobogo.com/DesignPatterns/command.php
#include <iostream>
#include <memory>

using namespace std;

class Command {
public:
  // declares an interface for executing an operation.
  virtual void execute() = 0;
  virtual ~Command() = default;

protected:
  Command() = default;
};

template <typename Receiver>
class SimpleCommand : public Command { // ConcreteCommand
public:
  typedef void (Receiver::*Action)();
  // defines a binding between a Receiver object and an action.
  SimpleCommand(std::shared_ptr<Receiver> receiver_, Action action_)
      : receiver(receiver_.get()), action(action_) {}
  SimpleCommand(const SimpleCommand &) = delete; // rule of three
  const SimpleCommand &operator=(const SimpleCommand &) = delete;
  // implements execute by invoking the corresponding operation(s) on Receiver.
  virtual void execute() { (receiver->*action)(); }

private:
  Receiver *receiver;
  Action action;
};

class MyClass { // Receiver
public:
  // knows how to perform the operations associated with carrying out a request.
  // Any class may serve as a Receiver.
  void action() { std::cout << "MyClass::action\n"; }
};

int main() {
  // The smart pointers prevent memory leaks.
  std::shared_ptr<MyClass> receiver = std::make_shared<MyClass>();
  // ...
  std::unique_ptr<Command> command =
      std::make_unique<SimpleCommand<MyClass>>(receiver, &MyClass::action);
  // ...
  command->execute();
}

/*

// Command Interface
class Command
{
public:
    virtual void execute() = 0;
};

// Receiver Class
class Light
{
public:
    void actionOn() {
        cout << "The light is on\n";
    }
    void actionOff() {
        cout << "The light is off\n";
    }
};

// Command for turning on the light
class LightOnCommand : public Command
{
public:
        LightOnCommand(Light *light) : mLight(light) {}
    void execute(){
        mLight->actionOn();
    }
private:
    Light *mLight;
};

// Command for turning off the light
class LightOffCommand : public Command
{
public:
        LightOffCommand(Light *light) : mLight(light) {}
    void execute(){
        mLight->actionOff();
    }
private:
    Light *mLight;
};

// Invoker
// Stores the ConcreteCommand object
class RemoteControl
{
public:
    void setCommand(Command *cmd) {
        mCmd = cmd;
    }

    void buttonPressed() {
        mCmd->execute();
    }
private:
    Command *mCmd;
};

// The client
int main()
{
    // Receiver
    Light *light = new Light;

    // concrete Command objects
    LightOnCommand *lightOn = new LightOnCommand(light);
    LightOffCommand *lightOff = new LightOffCommand(light);

    // invoker objects
    RemoteControl *control = new RemoteControl;

    // execute
    control->setCommand(lightOn);
    control->buttonPressed();
    control->setCommand(lightOff);
    control->buttonPressed();

    delete light, lightOn, lightOff, control;

    return 0;
}
*/