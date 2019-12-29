#include <iostream>
#include <memory>
/*
https://boost-experimental.github.io/di/cpp-london-2017/
https://github.com/stevef51/CPPServiceLocator
*/


namespace before
{

class GasEngine
{
public:
    void Start()
    {
        std::cout<<"I use gas as my fuel!"<<std::endl;
    }
};


class Car
{
public:
    Car()
    {
        std::shared_ptr<GasEngine> engine_ptr(new GasEngine());
        engine_ptr->Start();
    }
};


}//end of namespace before


namespace after
{
class IEngine
{
public:
    IEngine(){}

    void virtual Start(){}
};

class electricEngine: public IEngine
{
    void Start()
    {
        std::cout<<"I use electricity as my fuel!"<<std::endl;

    }
};

class gasEngine: public IEngine
{
    void Start()
    {
        std::cout<<"I use gas as my fuel!"<<std::endl;

    }
};


class Car
{
    IEngine *engine;
public:
    Car(IEngine *engine)
    {
        //std::shared_ptr<GasEngine> engine_ptr(new GasEngine());
        engine->Start();
    }
};

}


int main()
{
//before

    std::shared_ptr<before::Car> car_ptr(new before::Car());

//after

    std::shared_ptr<after::IEngine> gasEngine_ptr(new after::gasEngine());
    std::shared_ptr<after::IEngine> electricEngine_ptr(new after::electricEngine());
    std::shared_ptr<after::Car> electricCar_ptr(new after::Car(electricEngine_ptr.get()));
    std::shared_ptr<after::Car> gasCar_ptr(new after::Car(gasEngine_ptr.get()));

}
