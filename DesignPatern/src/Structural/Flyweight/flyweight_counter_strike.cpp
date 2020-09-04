#include <iostream>
#include <string>
#include <unordered_map>
#include <time.h>
#include <memory>
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



// A common interface for all players
class Player
{
public:
    void virtual assignWeapon(std::string weapon){}
    void virtual mission(){}
};

enum class playerType
{TERRORIST,COUNTERTRRRORIST};

// Terrorist must have weapon and mission
class Terrorist :public Player
{
    // Intrinsic Attribute (shared between all instances)
private:
    std::string TASK;

    // Extrinsic Attribute (can not be shared)
    std::string weapon;

public: Terrorist()
    {
        TASK = "PLANT A BOMB";
    }
    void assignWeapon(std::string weapon)
    {
        // Assign a weapon
        this->weapon = weapon;
    }
    void mission()
    {
        //Work on the Mission
        std::cout<<"Terrorist with weapon " << weapon << "|" << " Task is " << TASK<<std::endl;
    }
};

// CounterTerrorist must have weapon and mission
class CounterTerrorist: public Player
{
    // Intrinsic Attribute
private:
    std::string TASK;

    // Extrinsic Attribute
    std::string weapon;

public: CounterTerrorist()
    {
        TASK = "DIFFUSE BOMB";
    }
    void assignWeapon(std::string weapon)
    {
        this->weapon = weapon;
    }
    void mission()
    {
        std::cout<<"Counter Terrorist with weapon "<< weapon << "|" << " Task is " << TASK<<std::endl;
    }
};

//Claass used to get a playeer using HashMap (Returns
//an existing player if a player of given type exists.
//Else creates a new player and returns it.
class PlayerFactory
{
    /* unordered map stores the reference to the object of Terrorist(TS) or CounterTerrorist(CT).  */
private:
    // Method to get a player
public:
    static std::unordered_map<playerType, std::shared_ptr<Player> > hm;
    static std::shared_ptr<Player>  getPlayer(playerType type)
    {
        std::shared_ptr<Player> p = nullptr;

        /* If an object for TS or CT has already been created simply return its reference */
        if (hm.find(type) != hm.end())
                p = hm[type];
        else
        {
            /* create an object of TS/CT  */
            switch(type)
            {
            case playerType::TERRORIST:
                std::cout<<"Terrorist Created"<<std::endl;
                p.reset( new Terrorist());
                break;
            case playerType::COUNTERTRRRORIST:
                std::cout<<"Counter Terrorist Created"<<std::endl;
                p.reset( new CounterTerrorist());
                break;
            default :
                std::cout<<"Unreachable code!"<<std::endl;
            }

            // Once created insert it into the HashMap
            hm[type]= p;
        }
        return p;
    }
};



std::string weapons[]= {"AK-47", "Maverick", "Gut Knife", "Desert Eagle"};

// Utility methods to get a random player type and weapon using rand which generate a number between 0 and RAND_MAX
playerType getRandPlayerType()
{
    //Will return an integer between [0,2)
    return playerType(rand() % 2);
}
std::string getRandWeapon()
{
    // Return the weapon stored at index 'randInt'
    return weapons[rand() % 4];
}

std::unordered_map<playerType,std::shared_ptr<Player> > PlayerFactory::hm;

int main()
{
    /*It is important to only invoke the srand call ONCE at the beginning of the program. There is no need
    for repeat calls to seed the random number generator (in fact, it will make your number less evenly
    distributed). */
    srand (time(NULL));
    // All player types and weopons (used by getRandPlayerType() and getRandWeapon()
    int numberOfPlayer=20;
    for (int i = 0; i <numberOfPlayer; i++)
    {
        std::shared_ptr<Player>p  = PlayerFactory::getPlayer(getRandPlayerType());
        /* Assign a weapon chosen randomly uniformly from the weapon array  */
        p->assignWeapon(getRandWeapon());
        // Send this player on a mission
        p->mission();
    }

}
