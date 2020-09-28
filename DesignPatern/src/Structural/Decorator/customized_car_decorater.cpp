#include <iostream>
#include <string>

class Car
{
protected:
    std::string m_description;
public:
    Car()
    {
        m_description="Unkown Car";
    }
    virtual std::string getDescription()
    {
        return m_description;
    }
    virtual double getPrice()=0;

};

class BaseModel:public Car
{
public:
    double getPrice() override
    {
        return 35000.00;
    }
    BaseModel()
    {
        m_description="Base model";
    }
};

class OptionsDecorator:public Car
{
protected:
    Car *m_car;
public:
    OptionsDecorator(Car *car):m_car(car){}
    virtual std::string getDescription() = 0;
    virtual double getPrice() = 0;

};

class SoundSystem: public OptionsDecorator
{

public:
    SoundSystem(Car *car):OptionsDecorator(car){}

    double getPrice() override
    {
        return m_car->getPrice()+1000;
    }

    std::string getDescription() override
    {
        return  m_car->getDescription()+ " + Sound System";
    }
};

class Navigation: public OptionsDecorator
{

public:
    Navigation(Car *car):OptionsDecorator(car){}

    double getPrice() override
    {
        return m_car->getPrice()+500;
    }

    std::string getDescription() override
    {
        return  m_car->getDescription()+ " + Navigation";
    }


};
int main()
{
    Car *base_model=new BaseModel() ;
    Car *base_model_sound_system=new SoundSystem(base_model);
    Car *base_model_sound_system_navigan=new Navigation(base_model_sound_system);

    std::cout<<base_model_sound_system_navigan->getDescription()<<std::endl;
    std::cout<<"35000.00+1000+500="<<base_model_sound_system_navigan->getPrice()<<std::endl;
}
