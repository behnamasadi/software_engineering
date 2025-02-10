#include <iostream>
#include <list>
#include <memory>
#include <string>

// Forward declaration removed - MediatorInterface should be fully defined first

class ColleagueInterface;

// Mediator Interface
class MediatorInterface {
private:
  std::list<ColleagueInterface *> colleagueList;

public:
  virtual ~MediatorInterface() = default;

  void registerColleague(ColleagueInterface *colleague) {
    colleagueList.emplace_back(colleague);
  }

  const std::list<ColleagueInterface *> &getColleagueList() const {
    return colleagueList;
  }

  virtual void distributeMessage(
      const ColleagueInterface *,
      const std::string &) = 0; // Removed const to allow modification
};

// Colleague Interface
class ColleagueInterface {
protected:
  std::string name;

public:
  ColleagueInterface(const std::string &newName) : name(newName) {}

  std::string getName() const { return name; }

  virtual void sendMessage(MediatorInterface &, const std::string &) const = 0;
  virtual void receiveMessage(const ColleagueInterface *,
                              const std::string &) const = 0;

  virtual ~ColleagueInterface() = default;
};

// Concrete Colleague
class Colleague : public ColleagueInterface {
public:
  using ColleagueInterface::ColleagueInterface;

  void sendMessage(MediatorInterface &mediator,
                   const std::string &message) const override {
    mediator.distributeMessage(this, message);
  }

  void receiveMessage(const ColleagueInterface *sender,
                      const std::string &message) const override {
    std::cout << getName() << " received the message from " << sender->getName()
              << ": " << message << std::endl;
  }
};

// Concrete Mediator
class Mediator : public MediatorInterface {
public:
  void distributeMessage(const ColleagueInterface *sender,
                         const std::string &message) override {
    for (ColleagueInterface *x : getColleagueList()) {
      if (x != sender) // Don't send the message back to the sender
        x->receiveMessage(sender, message);
    }
  }
};

// Main function
int main() {
  Colleague bob("Bob"), sam("Sam"), frank("Frank"), tom("Tom");

  Mediator mediatorStaff, mediatorSamsBuddies;

  // Register all colleagues in the main mediator
  mediatorStaff.registerColleague(&bob);
  mediatorStaff.registerColleague(&sam);
  mediatorStaff.registerColleague(&frank);
  mediatorStaff.registerColleague(&tom);

  // Bob sends a message
  bob.sendMessage(mediatorStaff, "I'm quitting this job!");

  // Register Frank and Tom in a separate mediator for Sam's private group
  mediatorSamsBuddies.registerColleague(&frank);
  mediatorSamsBuddies.registerColleague(&tom);

  // Sam sends a message to his private group
  sam.sendMessage(mediatorSamsBuddies,
                  "Hooray! He's gone! Let's go for a drink, guys!");

  return 0;
}
