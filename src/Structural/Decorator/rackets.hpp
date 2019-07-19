#ifndef RACKETS_H
#define RACKETS_H

#include "tennisDecorator.hpp"

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

#endif // RACKETS_H
