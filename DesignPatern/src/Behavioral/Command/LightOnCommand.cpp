// https://www.bogotobogo.com/DesignPatterns/command.php
#include <iostream>
#include <memory>

using namespace std;

// Command Interface
class Command {
public:
  virtual void execute() = 0;
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
  LightOnCommand(Light *light) : mLight(light) {}
  void execute() { mLight->actionOn(); }

private:
  Light *mLight;
};

// Command for turning off the light
class LightOffCommand : public Command {
public:
  LightOffCommand(Light *light) : mLight(light) {}
  void execute() { mLight->actionOff(); }

private:
  Light *mLight;
};

// Invoker
// Stores the ConcreteCommand object
class RemoteControl {
public:
  void setCommand(Command *cmd) { mCmd = cmd; }

  void buttonPressed() { mCmd->execute(); }

private:
  Command *mCmd;
};

// The client
int main() {
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
