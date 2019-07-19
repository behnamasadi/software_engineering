#include "clayCourtBooking.hpp"
#include "grassCourtBooking.hpp"
#include "hardCourtBooking.hpp"

#include "rackets.hpp"
#include "ballPack.hpp"
#include "coaching.hpp"

#include <memory>

int main()
{
    courtBooking *cb1= new grassCourtBooking();
    cb1=new rackets(cb1);
    cb1=new ballPack(cb1);
    cb1=new coaching(cb1);

    std::cout<< "Costs:"<<std::endl;
    std::cout<< cb1->cost()<<std::endl;


}
