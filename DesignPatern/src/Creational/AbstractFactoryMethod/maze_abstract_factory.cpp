#include <vector>
#include <memory>


//namespace Before
//{

enum class  Direction{NORTH, SOUTH, WEST, EAST};

class MapSite
{
public:
    virtual void enter()=0;
};

class Wall :public MapSite
{
public:
    void  enter() override {}
};

class Room :public MapSite
{
    std::vector<MapSite *> sides;
public:
    Room(int roomNumber):roomNumber(roomNumber){}
    int roomNumber;
    void  enter() override {}
    MapSite* getSide(Direction){}
    void setSide(MapSite* mapSite,Direction direction){}
};

class Door :public MapSite
{
    Room* room1;
    Room* room2;
    bool openStatus;
public:
    Door(Room* room1= 0, Room* room2 = 0){}
    bool isOpen(){}
    void  enter() override {}

};

class Maze
{
    std::vector<Room *> rooms;
public:
    void addRoom(Room *){}
    Room * RoomsNo(int){}
};

//class MazeGame
//{
//    public:
//    Maze* CreateMaze ()
//    {
//        Maze* aMaze = new Maze;
//        Room* r1 = new Room(1);
//        Room* r2 = new Room(2);
//        Door* theDoor = new Door(r1, r2);
//        aMaze->addRoom(r1);
//        aMaze->addRoom(r2);
//        r1->setSide(North, new Wall);
//        r1->setSide(East, theDoor);
//        r1->setSide(South, new Wall);
//        r1->setSide(West, new Wall);
//        r2->setSide(North, new Wall);
//        r2->setSide(East, new Wall);
//        r2->setSide(South, new Wall);
//        r2->setSide(West, theDoor);
//    }
//};

//}


//namespace AbstractFactory
//{

//class MazeFactory
//{
//public:
//    MazeFactory();
//    virtual Maze* MakeMaze() const
//    { return new Maze; }
//    virtual Wall* MakeWall() const
//    { return new Wall; }
//    virtual Room* MakeRoom(int n) const
//    { return new Room(n); }
//    virtual Door* MakeDoor(Room* r1, Room* r2) const
//    { return new Door(r1, r2); }
//};


//class EnchantedMazeFactory : public MazeFactory
//{
//public:
//    EnchantedMazeFactory();
//    virtual Room* MakeRoom(int n) const
//    { return new EnchantedRoom(n, CastSpell()); }
//    virtual Door* MakeDoor(Room* r1, Room* r2) const
//    { return new DoorNeedingSpell(r1, r2); }
//    protected:
//    Spell* CastSpell() const;
//};
//}




int main()
{

/*

The real problem with this member function isn't its size but its
inflexibility. It hard-codes the maze layout.

Suppose you wanted to reuse an existing maze layout for a new game containing (of all
things) enchanted mazes. The enchanted maze game has new kinds of components, like
DoorNeedingSpell , a door that can be locked and opened subsequently only with a
spell; and EnchantedRoom , a room that can have unconventional items in it, like magic
keys or spells. How can you change CreateMaze easily so that it creates mazes with
these new classes of objects?

The creational patterns provide different ways to remove explicit
references to concrete classes from code that needs to instantiate them

*/

    Maze* aMaze = new Maze;
    Room* r1 = new Room(1);
    Room* r2 = new Room(2);
    Door* theDoor = new Door(r1, r2);
    aMaze->addRoom(r1);
    aMaze->addRoom(r2);
    r1->setSide(new Wall,Direction::NORTH);
    r1->setSide(theDoor,Direction::EAST);
    r1->setSide(new Wall,Direction::SOUTH );
    r1->setSide(new Wall,Direction::WEST );
    r2->setSide(new Wall, Direction::NORTH );
    r2->setSide(new Wall,Direction::EAST );
    r2->setSide(new Wall,Direction::SOUTH );
    r2->setSide(theDoor,Direction::WEST );
}
