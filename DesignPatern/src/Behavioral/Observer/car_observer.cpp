#include <memory>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>

class Observer;

class Car
{
    double m_speed;
    int m_temperature;
    std::vector<Observer *> m_ObserverList;
    //std::map<Observer *> m_ObserverMap;

    void notify();

    void attach(Observer *obs)
    {
        //observerList.push_back(obs);
    }
    void detach(Observer *obs)
    {
        //m_ObserverList.erase(std::remove(m_ObserverList.begin(), m_ObserverList.end(), obs), m_ObserverList.end());
    }

public:
    double getSpeed()
    {
        return m_speed;
    }
    void setSpeed(double speed)
    {
        m_speed=speed;
        notify();
    }

    int getTemperature()
    {
        return m_temperature;
    }
    void setTemperature(int temperature)
    {
        m_temperature=temperature;
        notify();
    }
};

class Observer
{
    std::string m_name;
protected:
    Car * m_car;
public:
    Observer(Car * car, std::string name):m_car(car),m_name(name){}
    void virtual update()=0;

};

void Car::notify()
{
    for(std::vector<Observer *>::iterator it=m_ObserverList.begin();it!=m_ObserverList.end();it++)
    {
        (*it)->update();
    }
}

class TemperatureObserver:public Observer
{
public:
    void update() override
    {
        std::cout<<"Car Temperature is: " <<m_car->getTemperature()<<std::endl;
    }

};
class SpeedObserver:public  Observer
{
public:
    void update() override
    {
        std::cout<<"Car Speed is: " <<m_car->getSpeed()<<std::endl;
    }

};
int main()
{
    std::vector<Observer *> observerList;
    SpeedObserver* speedObserver1, *speedObserver2;
    TemperatureObserver *temperatureObserver1, *temperatureObserver2,*temperatureObserver3;
    observerList.push_back(speedObserver1);
    observerList.push_back(temperatureObserver1);
    observerList.push_back(speedObserver2);
    observerList.push_back(temperatureObserver2);
    observerList.push_back(temperatureObserver3);
    std::cout<<observerList.size()<<std::endl;
    std::vector<Observer *>::iterator p = std::find (observerList.begin(), observerList.end(), speedObserver2);
    observerList.erase(p);
    std::cout<<observerList.size()<<std::endl;

}
