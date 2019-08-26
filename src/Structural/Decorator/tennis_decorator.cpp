#include <memory>
#include <iostream>
#include <string>



class courtBooking
{
    std::string info;
public:
    courtBooking(){}
    virtual int cost()
    {
        return 1000;
    }
};

class tennisDecorator: public courtBooking
{

public:
    int virtual cost(){}

};

class grassCourtBooking: public courtBooking
{
    public:
    grassCourtBooking(){}
    ~grassCourtBooking(){}
    int cost()
    {
        std::cout<<"Grass Court Booking: 8000" <<std::endl;
        return 8000;
    }
};

class coaching: public tennisDecorator
{
    courtBooking *cb;
public:
    coaching(courtBooking *cb):cb(cb){}

    int  cost() override
    {
        std::cout<<"coaching cost: 300" <<std::endl;

        return this->cb->cost()+300;
    }
};

class ballPack: public tennisDecorator
{
    courtBooking *cb;
public:
    ballPack(courtBooking *cb):cb(cb){}

    int  cost() override
    {
        std::cout<<"ballPack costs: 100" <<std::endl;
        return this->cb->cost()+100;
    }
};

class rackets: public tennisDecorator
{
    courtBooking *cb;
public:
    rackets(courtBooking *cb):cb(cb){}

    int  cost() override
    {
        std::cout<<"rackets cost: 200" <<std::endl;
        return this->cb->cost()+200;
    }
};

int main()
{
    courtBooking *grass_court= new grassCourtBooking();
    courtBooking * grass_court_rackets=new rackets(grass_court);
    courtBooking * grass_court_rackets_ballPack=new ballPack(grass_court_rackets);
    courtBooking * grass_court_rackets_ballPack_coaching=new coaching(grass_court_rackets_ballPack);

    std::cout<< "Costs:"<<std::endl;
    std::cout<< grass_court_rackets_ballPack_coaching->cost()<<std::endl;

    delete grass_court;
    delete grass_court_rackets;
    delete grass_court_rackets_ballPack;
    delete grass_court_rackets_ballPack_coaching;
}
