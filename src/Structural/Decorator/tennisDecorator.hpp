#ifndef TENNISDECORATOR_H
#define TENNISDECORATOR_H

#include "courtBooking.hpp"
#include <iostream>

class tennisDecorator: public courtBooking
{

public:
//    tennisDecorator()
//    {
//        std::cout<<"tennisDecorator constructor" <<std::endl;
//    }
    int virtual cost(){}

};

#endif // TENNISDECORATOR_H
