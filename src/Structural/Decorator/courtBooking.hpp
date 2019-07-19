#ifndef COURTBOOKING_H
#define COURTBOOKING_H

#include <string>

class courtBooking
{
    std::string info;
public:

    //courtBooking(std::string info):info(info){}
    courtBooking(){}
    void setInfo(std::string info)
    {
        this->info=info;
    }
    std::string getInfo();
    virtual int cost()
    {
        return 1000;
    }
};

#endif // COURTBOOKING_H
