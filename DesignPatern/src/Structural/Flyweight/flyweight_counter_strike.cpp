#include <iostream>
#include <string>
#include <unordered_map>
#include <time.h>
#include <memory>
#include <vector>
/*
Intrinsic: shared
Intrinsic state consists of information that is independent of the flyweight's context information.

Extrinsic: can not be shared
Extrinsic state cannot be shared, it depends on and varies with the Flyweight's context

The idea being that the memory it takes to store the extrinsic state need not be duplicated for every object.
Extrinsic state is stored or computed by the client and is passed to the flyweight when
an operation is invoked. Clients should not instantiate Flyweights directly, they should
obtain them exclusively from a FlyweightFactory object to ensure they are shared properly.

An good example of this categorisation is a graphical component such as a tooltip, whose intrinsic
data is the text to be displayed and the extrinsic data is the xx and yy coordinates on the screen.

*/


#include <iostream>
#include <unordered_map>
#include <vector>
#include <memory>
#include <cstdlib>
#include <ctime>

// Common interface for all players
class Player
{
public:
    virtual void equipWeapon(const std::string& weapon) = 0;
    virtual void performMission() const = 0;
    virtual ~Player() = default;  // Ensures proper polymorphic destruction
};

// Enum for player types
enum class PlayerType { TERRORIST, COUNTER_TERRORIST };

// Terrorist class (Flyweight)
class Terrorist : public Player
{
private:
    const std::string MISSION_GOAL = "Plant a bomb"; // Intrinsic state (shared)
    std::string weapon; // Extrinsic state (unique per instance)

public:
    void equipWeapon(const std::string& weapon) override
    {
        this->weapon = weapon;
    }

    void performMission() const override
    {
        std::cout << "Terrorist with weapon " << weapon 
                  << " | Mission: " << MISSION_GOAL << std::endl;
    }
};

// Counter-Terrorist class (Flyweight)
class CounterTerrorist : public Player
{
private:
    const std::string MISSION_GOAL = "Diffuse the bomb"; // Intrinsic state (shared)
    std::string weapon; // Extrinsic state (unique per instance)

public:
    void equipWeapon(const std::string& weapon) override
    {
        this->weapon = weapon;
    }

    void performMission() const override
    {
        std::cout << "Counter-Terrorist with weapon " << weapon 
                  << " | Mission: " << MISSION_GOAL << std::endl;
    }
};

// Factory class to manage Flyweight instances
class PlayerFactory
{
private:
    static std::unordered_map<PlayerType, std::shared_ptr<Player>> playerCache;

public:
    static std::shared_ptr<Player> getPlayer(PlayerType type)
    {
        auto it = playerCache.find(type);

        if (it != playerCache.end())
        {
            std::cout << "✅ Reusing existing player.\n";
            return it->second;
        }

        std::shared_ptr<Player> newPlayer = nullptr;

        switch (type)
        {
        case PlayerType::TERRORIST:
            std::cout << "🔥 Creating a new Terrorist.\n";
            newPlayer = std::make_shared<Terrorist>();
            break;
        case PlayerType::COUNTER_TERRORIST:
            std::cout << "🛡️ Creating a new Counter-Terrorist.\n";
            newPlayer = std::make_shared<CounterTerrorist>();
            break;
        default:
            throw std::runtime_error("Invalid Player Type");
        }

        playerCache[type] = newPlayer;
        return newPlayer;
    }
};

// Define static unordered_map
std::unordered_map<PlayerType, std::shared_ptr<Player>> PlayerFactory::playerCache;

// Utility function to get a random player type
PlayerType getRandomPlayerType()
{
    return static_cast<PlayerType>(rand() % 2);
}

// List of available weapons
std::string weapons[] = { "AK-47", "Maverick", "Gut Knife", "Desert Eagle" };

// Utility function to get a random weapon
std::string getRandomWeapon()
{
    return weapons[rand() % 4];
}

// Main execution
int main()
{
    srand(time(NULL));  // Seed random number generator

    std::vector<std::shared_ptr<Player>> gamePlayers;
    const int numPlayers = 20;

    for (int i = 0; i < numPlayers; ++i)
    {
        auto player = PlayerFactory::getPlayer(getRandomPlayerType());
        player->equipWeapon(getRandomWeapon());
        player->performMission();
    }

    return 0;
}
