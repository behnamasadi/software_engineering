#include <vector>
#include <memory>
#include <iostream>

// Enum for directions
enum class Direction { NORTH, SOUTH, WEST, EAST };

// Base class for maze components
class MapSite
{
public:
    virtual void enter() = 0;
    virtual ~MapSite() = default;
};

// Wall class
class Wall : public MapSite
{
public:
    void enter() override { std::cout << "You hit a wall.\n"; }
};

// Room class
class Room : public MapSite
{
private:
    int roomNumber;
    std::vector<std::unique_ptr<MapSite>> sides{4};

public:
    explicit Room(int num) : roomNumber(num) {}

    void enter() override { std::cout << "Entering room " << roomNumber << ".\n"; }

    void addSide(Direction dir, std::unique_ptr<MapSite> site)
    {
        sides[static_cast<int>(dir)] = std::move(site);
    }
};

// Door class
class Door : public MapSite
{
private:
    Room* room1;
    Room* room2;
    bool isOpen;

public:
    Door(Room* r1, Room* r2) : room1(r1), room2(r2), isOpen(false) {}

    void enter() override
    {
        if (isOpen)
            std::cout << "Passing through the door.\n";
        else
            std::cout << "The door is locked.\n";
    }

    void openDoor() { isOpen = true; }
};

// Maze class
class Maze
{
private:
    std::vector<std::unique_ptr<Room>> rooms;

public:
    void addRoom(std::unique_ptr<Room> room)
    {
        rooms.push_back(std::move(room));
    }
};

// Abstract Factory for creating Maze components
class MazeFactory
{
public:
    virtual std::unique_ptr<Maze> createMaze() const
    {
        return std::make_unique<Maze>();
    }

    virtual std::unique_ptr<Room> createRoom(int n) const
    {
        return std::make_unique<Room>(n);
    }

    virtual std::unique_ptr<Wall> createWall() const
    {
        return std::make_unique<Wall>();
    }

    virtual std::unique_ptr<Door> createDoor(Room* r1, Room* r2) const
    {
        return std::make_unique<Door>(r1, r2);
    }

    virtual ~MazeFactory() = default;
};

// Specialized Factory for an Enchanted Maze
class EnchantedMazeFactory : public MazeFactory
{
public:
    std::unique_ptr<Room> createRoom(int n) const override
    {
        std::cout << "Creating an enchanted room " << n << ".\n";
        return std::make_unique<Room>(n); // Replace with EnchantedRoom if needed
    }

    std::unique_ptr<Door> createDoor(Room* r1, Room* r2) const override
    {
        std::cout << "Creating a magical door.\n";
        return std::make_unique<Door>(r1, r2); // Replace with DoorNeedingSpell if needed
    }
};

// MazeGame class to assemble the Maze
class MazeGame
{
public:
    std::unique_ptr<Maze> createMaze(const MazeFactory& factory)
    {
        auto maze = factory.createMaze();
        auto r1 = factory.createRoom(1);
        auto r2 = factory.createRoom(2);
        auto door = factory.createDoor(r1.get(), r2.get());

        // Setting sides for Room 1
        r1->addSide(Direction::NORTH, factory.createWall());
        r1->addSide(Direction::EAST, std::make_unique<Door>(*door));
        r1->addSide(Direction::SOUTH, factory.createWall());
        r1->addSide(Direction::WEST, factory.createWall());

        // Setting sides for Room 2
        r2->addSide(Direction::NORTH, factory.createWall());
        r2->addSide(Direction::EAST, factory.createWall());
        r2->addSide(Direction::SOUTH, factory.createWall());
        r2->addSide(Direction::WEST, std::make_unique<Door>(*door));

        maze->addRoom(std::move(r1));
        maze->addRoom(std::move(r2));

        return maze;
    }
};

// Main function
int main()
{
    std::cout << "\n🛠️ Creating a Normal Maze\n";
    MazeFactory normalFactory;
    MazeGame game;
    auto normalMaze = game.createMaze(normalFactory);

    std::cout << "\n🪄 Creating an Enchanted Maze\n";
    EnchantedMazeFactory enchantedFactory;
    auto enchantedMaze = game.createMaze(enchantedFactory);

    return 0;
}
