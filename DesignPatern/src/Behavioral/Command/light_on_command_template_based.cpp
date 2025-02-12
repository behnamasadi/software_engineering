#include <iostream>
#include <memory>
#include <functional>

using namespace std;

class Operation {
public:
    // Declares an interface for triggering an action.
    virtual void run() = 0;
    virtual ~Operation() = default;

protected:
    Operation() = default;
};

template <typename Receiver>
class ActionInvoker : public Operation { // Concrete Command
public:
    using Action = std::function<void(Receiver&)>;

    // Binds a Receiver object with an action function.
    ActionInvoker(shared_ptr<Receiver> receiver_, Action action_)
        : receiver(receiver_), action(action_) {}

    ActionInvoker(const ActionInvoker&) = delete; // Rule of three
    const ActionInvoker& operator=(const ActionInvoker&) = delete;

    // Triggers the action on the receiver.
    virtual void run() override { action(*receiver); }

private:
    shared_ptr<Receiver> receiver;
    Action action;
};

class MyClass { // Receiver
public:
    void performTask() { cout << "MyClass is executing a task...\n"; }
};

int main() {
    shared_ptr<MyClass> receiver = make_shared<MyClass>();

    // Using std::function to bind a member function to an ActionInvoker.
    unique_ptr<Operation> command =
        make_unique<ActionInvoker<MyClass>>(receiver, &MyClass::performTask);

    command->run();
}
