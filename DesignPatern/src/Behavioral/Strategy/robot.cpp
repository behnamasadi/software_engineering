// Strategy — robot behavior with composable parts.
//
// The "before" path uses inheritance to combine search/attack/defend:
// every new combination needs a new subclass (LinearPunchRun, SpiralPinchRun,
// LinearPinchHide, ...). N×M×K classes for N×M×K combinations.
//
// The "after" path makes each axis its own Strategy and composes them at
// runtime. New combinations are constructor arguments, not new classes.

#include <iostream>
#include <memory>
#include <utility>

namespace before_inheritance_explosion {

// One subclass per (search, attack, defend) combination.
class Robot {
public:
    virtual ~Robot() = default;
    virtual void search() = 0;
    virtual void attack() = 0;
    virtual void defend() = 0;
};

class LinearPunchRun : public Robot {
public:
    void search() override { std::cout << "  search: linear\n"; }
    void attack() override { std::cout << "  attack: punch\n"; }
    void defend() override { std::cout << "  defend: run\n"; }
};

class SpiralPinchRun : public Robot {
public:
    void search() override { std::cout << "  search: spiral\n"; }
    void attack() override { std::cout << "  attack: pinch\n"; }
    void defend() override { std::cout << "  defend: run\n"; }
};
// ... and many more for every other combination.

}  // namespace before_inheritance_explosion

namespace after_strategy {

class SearchStrategy { public: virtual ~SearchStrategy() = default; virtual void run() = 0; };
class AttackStrategy { public: virtual ~AttackStrategy() = default; virtual void run() = 0; };
class DefendStrategy { public: virtual ~DefendStrategy() = default; virtual void run() = 0; };

class LinearSearch : public SearchStrategy { public: void run() override { std::cout << "  search: linear\n"; } };
class SpiralSearch : public SearchStrategy { public: void run() override { std::cout << "  search: spiral\n"; } };
class Punch        : public AttackStrategy { public: void run() override { std::cout << "  attack: punch\n";  } };
class Pinch        : public AttackStrategy { public: void run() override { std::cout << "  attack: pinch\n";  } };
class Run          : public DefendStrategy { public: void run() override { std::cout << "  defend: run\n";    } };
class Hide         : public DefendStrategy { public: void run() override { std::cout << "  defend: hide\n";   } };

class Robot {
public:
    Robot(std::unique_ptr<SearchStrategy> s,
          std::unique_ptr<AttackStrategy> a,
          std::unique_ptr<DefendStrategy> d)
        : search_(std::move(s)), attack_(std::move(a)), defend_(std::move(d)) {}

    void run() { search_->run(); attack_->run(); defend_->run(); }

private:
    std::unique_ptr<SearchStrategy> search_;
    std::unique_ptr<AttackStrategy> attack_;
    std::unique_ptr<DefendStrategy> defend_;
};

}  // namespace after_strategy

int main() {
    std::cout << "before (inheritance):\n";
    before_inheritance_explosion::LinearPunchRun r1;
    r1.search(); r1.attack(); r1.defend();

    std::cout << "after (composition):\n";
    after_strategy::Robot composed(
        std::make_unique<after_strategy::SpiralSearch>(),
        std::make_unique<after_strategy::Pinch>(),
        std::make_unique<after_strategy::Hide>());
    composed.run();
}
