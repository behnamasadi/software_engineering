#ifndef BALLPACK_H
#define BALLPACK_H

#include "tennisDecorator.hpp"

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

#endif // BALLPACK_H
