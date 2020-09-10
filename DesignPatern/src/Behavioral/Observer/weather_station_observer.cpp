#include <vector>

class IObserver;

class IObservable
{

public:
    std::vector<IObserver *> observers;
    void virtual add(IObserver *observer);
    void virtual remove(IObserver *observer);
    void virtual notify();//this will call IObserver.update()
};

class IObserver
{
public:
    void update(){}
};

void IObservable::add(IObserver *observer)
{

}

void IObservable::remove(IObserver *observer)
{

}

void IObservable::notify()
{

}


class weatherStation : public IObservable
{
    int temperatur;
public:
/*
    This method is specific to the weatherStation and for other IObservable is meaning less,
    that's why it is here and not in IObservable
*/
    weatherStation()
    {
        temperatur=10;
    }
    int getTemperatur()
    {
        return temperatur;
    }
    void add(IObserver *observer) override
    {
        observers.push_back(observer);
    }

    void notify() override
    {
        for(std::size_t i=0;i< observers.size();i++)
        {
            observers[i]->update();
        }
    }
};


// class phoneDisplay: public IObserver
// {
// public:
//     weatherStation * weatherStation;
//     phoneDisplay(IObservable * weatherStation):weatherStation(weatherStation){}
//     void update() override
//     {
//         weatherStation->
//     }
// 
// 
// };
// 
// class windowsDisplay: public IObserver
// {
//     public:
//     IObservable * weatherStation;
//     windowsDisplay(IObservable * weatherStation):weatherStation(weatherStation){}
// };
// 
// 
// 
// 
// int main()
// {
//     weatherStation *myweatherStation=new weatherStation();
// 
//     phoneDisplay *phoneDisplay1=new phoneDisplay(myweatherStation);
//     windowsDisplay *windowsDisplay1=new windowsDisplay(myweatherStation);
// 
//     myweatherStation->add(phoneDisplay1);
//     myweatherStation->add(windowsDisplay1);
//     myweatherStation->notify();
// }
int main()
{
    
}
