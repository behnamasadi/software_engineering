// Factory Method — before/after.
//
// "Before": every site that needs a Stooge has its own if/else picking which
// concrete subclass to new. The selection logic is duplicated everywhere.
//
// "After": one static factory method lives next to the type. Adding a new
// stooge means adding one branch, not editing every call site.

#include <iostream>
#include <memory>
#include <vector>

namespace before_hardcoded {

class Stooge {
public:
    virtual ~Stooge() = default;
    virtual void perform() = 0;
};

class Larry : public Stooge {
public:
    void perform() override { std::cout << "  Larry: poke eyes\n"; }
};
class Moe : public Stooge {
public:
    void perform() override { std::cout << "  Moe: slap head\n"; }
};
class Curly : public Stooge {
public:
    void perform() override { std::cout << "  Curly: suffer abuse\n"; }
};

}  // namespace before_hardcoded

namespace after_factory_method {

class Stooge {
public:
    virtual ~Stooge() = default;
    virtual void perform() = 0;

    // Factory Method.
    static std::unique_ptr<Stooge> create(int choice);
};

class Larry : public Stooge {
public:
    void perform() override { std::cout << "  Larry: poke eyes\n"; }
};
class Moe : public Stooge {
public:
    void perform() override { std::cout << "  Moe: slap head\n"; }
};
class Curly : public Stooge {
public:
    void perform() override { std::cout << "  Curly: suffer abuse\n"; }
};

std::unique_ptr<Stooge> Stooge::create(int choice) {
    switch (choice) {
        case 1:  return std::make_unique<Larry>();
        case 2:  return std::make_unique<Moe>();
        default: return std::make_unique<Curly>();
    }
}

}  // namespace after_factory_method

int main() {
    std::cout << "--- before (hardcoded) ---\n";
    {
        std::vector<std::unique_ptr<before_hardcoded::Stooge>> stooges;
        stooges.push_back(std::make_unique<before_hardcoded::Larry>());
        stooges.push_back(std::make_unique<before_hardcoded::Moe>());
        stooges.push_back(std::make_unique<before_hardcoded::Curly>());
        for (auto& s : stooges) s->perform();
    }

    std::cout << "--- after (factory method) ---\n";
    {
        std::vector<std::unique_ptr<after_factory_method::Stooge>> stooges;
        for (int choice : {1, 2, 3}) {
            stooges.push_back(after_factory_method::Stooge::create(choice));
        }
        for (auto& s : stooges) s->perform();
    }
}
