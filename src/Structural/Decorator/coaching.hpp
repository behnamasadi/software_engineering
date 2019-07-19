#ifndef COACHING_H
#define COACHING_H

#include "tennisDecorator.hpp"

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
#endif // COACHING_H
