// Abstract Factory — maze components.
// MazeFactory produces walls, rooms, doors. Subclasses (e.g.
// EnchantedMazeFactory) substitute themed variants without changing the
// MazeGame assembly code.

#include <array>
#include <iostream>
#include <memory>
#include <utility>
#include <vector>

enum class Direction { North = 0, South = 1, West = 2, East = 3 };

class MapSite {
public:
    virtual ~MapSite() = default;
    virtual void enter() = 0;
};

class Wall : public MapSite {
public:
    void enter() override { std::cout << "  hit a wall\n"; }
};

class Room : public MapSite {
public:
    explicit Room(int number) : number_(number) {}

    void enter() override { std::cout << "  entering room " << number_ << '\n'; }

    void setSide(Direction dir, std::shared_ptr<MapSite> site) {
        sides_[static_cast<int>(dir)] = std::move(site);
    }

private:
    int number_;
    std::array<std::shared_ptr<MapSite>, 4> sides_;
};

class Door : public MapSite {
public:
    Door(std::shared_ptr<Room> a, std::shared_ptr<Room> b)
        : a_(std::move(a)), b_(std::move(b)) {}

    void enter() override {
        if (open_) std::cout << "  passing through the door\n";
        else       std::cout << "  the door is locked\n";
    }

    void open() { open_ = true; }

private:
    std::shared_ptr<Room> a_, b_;
    bool open_ = false;
};

class Maze {
public:
    void addRoom(std::shared_ptr<Room> room) { rooms_.push_back(std::move(room)); }
    std::size_t roomCount() const { return rooms_.size(); }

private:
    std::vector<std::shared_ptr<Room>> rooms_;
};

class MazeFactory {
public:
    virtual ~MazeFactory() = default;

    virtual std::unique_ptr<Maze>         createMaze()                                            const { return std::make_unique<Maze>(); }
    virtual std::shared_ptr<Wall>         createWall()                                            const { return std::make_shared<Wall>(); }
    virtual std::shared_ptr<Room>         createRoom(int n)                                       const { return std::make_shared<Room>(n); }
    virtual std::shared_ptr<Door>         createDoor(std::shared_ptr<Room> a, std::shared_ptr<Room> b) const { return std::make_shared<Door>(std::move(a), std::move(b)); }
};

class EnchantedMazeFactory : public MazeFactory {
public:
    std::shared_ptr<Room> createRoom(int n) const override {
        std::cout << "  [enchanted] creating room " << n << '\n';
        return std::make_shared<Room>(n);
    }
    std::shared_ptr<Door> createDoor(std::shared_ptr<Room> a, std::shared_ptr<Room> b) const override {
        std::cout << "  [enchanted] creating magical door\n";
        return std::make_shared<Door>(std::move(a), std::move(b));
    }
};

class MazeGame {
public:
    std::unique_ptr<Maze> create(const MazeFactory& factory) {
        auto maze = factory.createMaze();
        auto r1   = factory.createRoom(1);
        auto r2   = factory.createRoom(2);
        auto door = factory.createDoor(r1, r2);  // door is shared between both rooms

        r1->setSide(Direction::North, factory.createWall());
        r1->setSide(Direction::East,  door);
        r1->setSide(Direction::South, factory.createWall());
        r1->setSide(Direction::West,  factory.createWall());

        r2->setSide(Direction::North, factory.createWall());
        r2->setSide(Direction::East,  factory.createWall());
        r2->setSide(Direction::South, factory.createWall());
        r2->setSide(Direction::West,  door);

        maze->addRoom(std::move(r1));
        maze->addRoom(std::move(r2));
        return maze;
    }
};

int main() {
    MazeGame game;

    std::cout << "--- normal maze ---\n";
    MazeFactory normal;
    auto m1 = game.create(normal);
    std::cout << "  rooms = " << m1->roomCount() << '\n';

    std::cout << "--- enchanted maze ---\n";
    EnchantedMazeFactory enchanted;
    auto m2 = game.create(enchanted);
    std::cout << "  rooms = " << m2->roomCount() << '\n';
}
