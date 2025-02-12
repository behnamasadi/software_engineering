#include <iostream>
#include <memory>

class Creature {
public:
    virtual ~Creature() = default;
    virtual void makeSound() const = 0;
    virtual std::string getType() const = 0;
};

class Hound : public Creature {
public:
    void makeSound() const override { std::cout << "Bark! (Hound)\n"; }
    std::string getType() const override { return "Hound"; }
};

class SilentCreature : public Creature {
public:
    void makeSound() const override {} // No sound
    std::string getType() const override { return "Silent"; }
};

void interactWithCreature(const Creature& creature) {
    std::cout << "Creature type: " << creature.getType() << " - ";
    creature.makeSound();
}

// Function that handles both real creatures and silent ones safely.
void interactWithCreature(const Creature* creature) {
    if (creature) {
        std::cout << "Pointer-based Creature type: " << creature->getType() << " - ";
        creature->makeSound();
    } else {
        std::cout << "Received a null pointer. No action taken.\n";
    }
}

int main() {
    std::unique_ptr<Creature> silentPtr = std::make_unique<SilentCreature>();
    interactWithCreature(silentPtr.get());

    SilentCreature silentInstance;
    interactWithCreature(silentInstance);

    std::unique_ptr<Creature> hound = std::make_unique<Hound>();
    interactWithCreature(hound.get());

    return 0;
}
