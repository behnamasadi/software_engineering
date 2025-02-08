#include <iostream>
#include <memory>

using namespace std;

// Command Interface
class Command {
public:
  virtual void execute() = 0;
  virtual ~Command() =
      default; // FIX: Virtual destructor to prevent memory leaks
};

// Receiver Class
class Light {
public:
  void actionOn() { cout << "The light is on\n"; }
  void actionOff() { cout << "The light is off\n"; }
};

// Command for turning on the light
class LightOnCommand : public Command {
public:
  explicit LightOnCommand(shared_ptr<Light> light) : mLight(light) {}
  void execute() override { mLight->actionOn(); }

private:
  shared_ptr<Light> mLight; // FIX: Use smart pointer to manage memory
};

// Command for turning off the light
class LightOffCommand : public Command {
public:
  explicit LightOffCommand(shared_ptr<Light> light) : mLight(light) {}
  void execute() override { mLight->actionOff(); }

private:
  shared_ptr<Light> mLight;
};

// Invoker (Stores the ConcreteCommand object)
class RemoteControl {
public:
  void setCommand(shared_ptr<Command> cmd) { mCmd = cmd; }
  void buttonPressed() {
    if (mCmd)
      mCmd->execute(); // FIX: Prevent nullptr dereference
  }

private:
  shared_ptr<Command> mCmd; // FIX: Use shared_ptr to manage ownership
};

// The client
int main() {
  // Receiver
  auto light = make_shared<Light>();

  // Concrete Command objects
  auto lightOn = make_shared<LightOnCommand>(light);
  auto lightOff = make_shared<LightOffCommand>(light);

  // Invoker object
  RemoteControl control;

  // Execute
  control.setCommand(lightOn);
  control.buttonPressed();
  control.setCommand(lightOff);
  control.buttonPressed();

  return 0; // Smart pointers handle cleanup automatically
}
