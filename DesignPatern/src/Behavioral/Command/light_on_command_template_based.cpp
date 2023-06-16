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
