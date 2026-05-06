// Flyweight — share the team-level state across all players on a team. Each
// Player flyweight carries only the *intrinsic* state (the team's mission
// goal). The *extrinsic* state (current weapon) is passed in at call time, so
// many game-world entities can share two Player objects total — one
// Terrorist, one CounterTerrorist — instead of one per player.
//
// Bug fix vs. earlier version: weapon used to be stored on the flyweight,
// which means every "player" mutated the same shared object — defeating the
// pattern. Weapon is extrinsic and lives on the call site, not the flyweight.

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

class Player {
public:
    virtual ~Player() = default;
    virtual void performMission(const std::string& weapon) const = 0;
};

enum class PlayerType { TERRORIST, COUNTER_TERRORIST };

class Terrorist : public Player {
public:
    void performMission(const std::string& weapon) const override {
        std::cout << "Terrorist with " << weapon << " | mission: " << goal_ << '\n';
    }

private:
    const std::string goal_ = "plant the bomb";
};

class CounterTerrorist : public Player {
public:
    void performMission(const std::string& weapon) const override {
        std::cout << "Counter-Terrorist with " << weapon
                  << " | mission: " << goal_ << '\n';
    }

private:
    const std::string goal_ = "diffuse the bomb";
};

class PlayerFactory {
public:
    static const Player& get(PlayerType type) {
        auto it = cache_.find(type);
        if (it != cache_.end()) return *it->second;

        std::unique_ptr<Player> p;
        switch (type) {
            case PlayerType::TERRORIST:
                std::cout << "Factory: creating Terrorist flyweight\n";
                p = std::make_unique<Terrorist>();
                break;
            case PlayerType::COUNTER_TERRORIST:
                std::cout << "Factory: creating CounterTerrorist flyweight\n";
                p = std::make_unique<CounterTerrorist>();
                break;
        }
        return *(cache_[type] = std::move(p));
    }

private:
    static std::unordered_map<PlayerType, std::unique_ptr<Player>> cache_;
};

std::unordered_map<PlayerType, std::unique_ptr<Player>> PlayerFactory::cache_;

int main() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    const std::vector<std::string> weapons = {"AK-47", "Maverick", "Gut Knife", "Desert Eagle"};

    for (int i = 0; i < 10; ++i) {
        auto type = static_cast<PlayerType>(std::rand() % 2);
        const Player& p = PlayerFactory::get(type);
        p.performMission(weapons[std::rand() % weapons.size()]);
    }
}
