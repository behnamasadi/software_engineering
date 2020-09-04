//https://www.geeksforgeeks.org/mediator-design-pattern/
#include <iostream>
#include <string>
#include <memory>


class Runway;
class Flight;

class  IATCMediator
{
public:

    void registerRunway(Runway *runway){}

    void registerFlight(Flight *flight){}

    bool isLandingOk(){}

    void setLandingStatus(bool status){}
};

class ATCMediator : public IATCMediator
{

private:
    Flight *flight;
    Runway *runway;

    public:
    bool land;

    void registerRunway(Runway *runway)
    {
        this->runway = runway;
    }

    void registerFlight(Flight *flight)
    {
        this->flight = flight;
    }

    bool isLandingOk()
    {
        return land;
    }


    void setLandingStatus(bool status)
    {
        land = status;
    }
};

class  Command
{
public:
    void land();
};

class Flight : public Command
{
private:
    IATCMediator *atcMediator;

public:
    Flight(IATCMediator *atcMediator)
    {
        this->atcMediator = atcMediator;
    }

    void land()
    {
        if (atcMediator->isLandingOk())
        {
            std::cout<<"Successfully Landed."<<std::endl;
            atcMediator->setLandingStatus(true);
        }
        else
            std::cout<<"Waiting for landing."<<std::endl;
    }

    void getReady()
    {
        std::cout<<"Ready for landing."<<std::endl;
    }

};

class Runway: public Command
{
private:
    IATCMediator *atcMediator;

public:
    Runway(IATCMediator *atcMediator)
    {
        this->atcMediator = atcMediator;
        atcMediator->setLandingStatus(true);
    }


    void land()
    {
        std::cout<<"Landing permission granted."<<std::endl;
        atcMediator->setLandingStatus(true);
    }

};


int main()
{

    IATCMediator *atcMediator = new ATCMediator();
    Flight *sparrow101 = new Flight(atcMediator);
    Runway *mainRunway = new Runway(atcMediator);
    atcMediator->registerFlight(sparrow101);
    atcMediator->registerRunway(mainRunway);
    sparrow101->getReady();
    mainRunway->land();
    sparrow101->land();

}
