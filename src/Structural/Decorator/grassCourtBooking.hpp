#ifndef GRASSCOURTBOOKING_H
#define GRASSCOURTBOOKING_H

#include "courtBooking.hpp"
#include <iostream>

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

#endif // GRASSCOURTBOOKING_H
