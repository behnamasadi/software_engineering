//https://www.geeksforgeeks.org/mediator-design-pattern/
#include <iostream>
#include <string>
#include <memory>


class Runway;
class Flight;

class  IAirTrafficControlMediator
{
public:

    virtual void registerRunway(Runway *runway)=0;

    virtual void registerFlight(Flight *flight)=0;

    virtual bool isLandingOk()=0;

    virtual void setLandingStatus(bool status)=0;
};

class AirTrafficControlMediator : public IAirTrafficControlMediator
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
    virtual void land()=0;
};

class Flight : public Command
{
private:
    IAirTrafficControlMediator *AirTrafficControlMediator;

public:
    Flight(IAirTrafficControlMediator *AirTrafficControlMediator)
    {
        this->AirTrafficControlMediator = AirTrafficControlMediator;
    }

    void land()
    {
        if (AirTrafficControlMediator->isLandingOk())
        {
            std::cout<<"Successfully Landed."<<std::endl;
            AirTrafficControlMediator->setLandingStatus(true);
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
    IAirTrafficControlMediator *AirTrafficControlMediator;

public:
    Runway(IAirTrafficControlMediator *AirTrafficControlMediator)
    {
        this->AirTrafficControlMediator = AirTrafficControlMediator;
        AirTrafficControlMediator->setLandingStatus(true);
    }


    void land()
    {
        std::cout<<"Landing permission granted."<<std::endl;
        AirTrafficControlMediator->setLandingStatus(true);
    }

};


int main()
{

    IAirTrafficControlMediator *airTrafficControlMediator = new AirTrafficControlMediator();
    Flight *sparrow101 = new Flight(airTrafficControlMediator);
    Runway *mainRunway = new Runway(airTrafficControlMediator);
    airTrafficControlMediator->registerFlight(sparrow101);
    airTrafficControlMediator->registerRunway(mainRunway);
    sparrow101->getReady();
    mainRunway->land();
    sparrow101->land();

}
