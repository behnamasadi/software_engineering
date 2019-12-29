#include <iostream>
#include <string>

enum class CarType
{
    MICRO, MINI, LUXURY
};

std::string ToString(CarType v)
{
    switch (v)
    {
        case CarType::MICRO:   return "MICRO";
        case CarType::MINI:   return "MINI";
        case CarType::LUXURY: return "LUXURY";
        default:      return "[Unknown]";
    }
}

enum class Location
{
  DEFAULT, USA, INDIA
};

std::string ToString(Location v)
{
    switch (v)
    {
        case Location::DEFAULT:   return "DEFAULT";
        case Location::USA:   return "USA";
        case Location::INDIA: return "INDIA";
        default:      return "[Unknown]";
    }
}

class Car
{
private:
    CarType model ;
    Location location;

public:

    Car(CarType model, Location location)
    {
        this->model = model;
        this->location = location;
    }

    virtual void construct(){}



    CarType getModel()
    {
        return model;
    }

    void setModel(CarType model)
    {
        this->model = model;
    }

    Location getLocation()
    {
        return location;
    }

    void setLocation(Location location)
    {
        this->location = location;
    }


    std::string toString()
    {
        return "CarModel - "+ ToString(model) + " located in "+ToString(location);
    }
};

class LuxuryCar :public Car
{
public:
    LuxuryCar(Location location):Car(CarType::LUXURY, location)
    {

        construct();
    }

    void construct()
    {
        std::cout<<"Connecting to luxury car"<<std::endl;
    }
};

class MicroCar : public Car
{
public:
    MicroCar(Location location):Car(CarType::MICRO, location)
    {
        construct();
    }

    void construct()
    {
         std::cout<<"Connecting to Micro Car "<<std::endl;
    }
};

class MiniCar : public Car
{
public:
    MiniCar(Location location):Car(CarType::MINI,location)
    {
        construct();
    }

    void construct()
    {
         std::cout<<"Connecting to Mini car"<<std::endl;
    }
};

class INDIACarFactory
{
public:
    static Car* buildCar(CarType model)
    {
        Car *car;
        switch (model)
        {
            case CarType::MICRO:
                car = new MicroCar(Location::INDIA);
                break;

            case CarType::MINI:
                car = new MiniCar(Location::INDIA);
                break;

            case CarType::LUXURY:
                car = new LuxuryCar(Location::INDIA);
                break;

                default:
                break;

        }
        return car;
    }
};

class DefaultCarFactory
{
public:
    static Car* buildCar(CarType model)
    {
        Car *car;
        switch (model)
        {
            case CarType::MICRO:
                car = new MicroCar(Location::DEFAULT);
                break;

            case CarType::MINI:
                car = new MiniCar(Location::DEFAULT);
                break;

            case CarType::LUXURY:
                car = new LuxuryCar(Location::DEFAULT);
                break;

                default:
                break;

        }
        return car;
    }
};


class USACarFactory
{
public:
    static Car* buildCar(CarType model)
    {
        Car *car;
        switch (model)
        {
            case CarType::MICRO:
                car = new MicroCar(Location::USA);
                break;

            case CarType::MINI:
                car = new MiniCar(Location::USA);
                break;

            case CarType::LUXURY:
                car = new LuxuryCar(Location::USA);
                break;

                default:
                break;

        }
        return car;
    }
};


class CarFactory
{

public:
    static Car* buildCar(CarType type)
    {
        Car *car;
        // We can add any GPS Function here which
        // read location property somewhere from configuration
        // and use location specific car factory
        // Currently I'm just using INDIA as Location
        Location location = Location::INDIA;

        switch(location)
        {
            case Location::USA:
                car = USACarFactory::buildCar(type);
                break;

            case Location::INDIA:
                car = INDIACarFactory::buildCar(type);
                break;

            default:
                car = DefaultCarFactory::buildCar(type);

        }

        return car;

    }
};

int main()
{
    std::cout<<CarFactory::buildCar(CarType::MICRO)->toString()<<std::endl;
    std::cout<<CarFactory::buildCar(CarType::MINI)->toString()<<std::endl;
    std::cout<<CarFactory::buildCar(CarType::LUXURY)->toString()<<std::endl;


}
