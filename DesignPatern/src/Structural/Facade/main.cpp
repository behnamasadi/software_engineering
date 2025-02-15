#include <iostream>
#include <memory>
#include <string>

using namespace std;

// Alarm System
class Alarm
{
public:
    void turnOn()
    {
        cout << "🔔 Alarm is activated. House is secured." << endl;
    }

    void turnOff()
    {
        cout << "🔕 Alarm is deactivated. You can enter the house." << endl;
    }
};

// Air Conditioner System
class AirConditioner
{
public:
    void turnOn()
    {
        cout << "❄️ Air Conditioner is now ON." << endl;
    }

    void turnOff()
    {
        cout << "🔥 Air Conditioner is now OFF." << endl;
    }
};

// Television System
class Television
{
public:
    void turnOn()
    {
        cout << "📺 TV is now ON." << endl;
    }

    void turnOff()
    {
        cout << "📴 TV is now OFF." << endl;
    }
};

// Facade for controlling the house devices
class SmartHomeFacade
{
private:
    unique_ptr<Alarm> alarm;
    unique_ptr<AirConditioner> ac;
    unique_ptr<Television> tv;

public:
    SmartHomeFacade()
        : alarm(make_unique<Alarm>()),
          ac(make_unique<AirConditioner>()),
          tv(make_unique<Television>())
    {
    }

    void leaveHome()
    {
        cout << "\n🏠 Preparing house for leaving..." << endl;
        ac->turnOff();
        tv->turnOff();
        alarm->turnOn();
    }

    void returnHome()
    {
        cout << "\n🏠 Preparing house for arrival..." << endl;
        alarm->turnOff();
        ac->turnOn();
        tv->turnOn();
    }
};

int main()
{
    SmartHomeFacade myHome;

    // Thanks to the Facade, we control all devices with just two functions
    myHome.leaveHome();
    myHome.returnHome();

    return 0;
}
