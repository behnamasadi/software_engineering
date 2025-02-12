#include <iostream>
#include <vector>
#include <memory>
#include <algorithm> // for std::remove_if

// Forward declaration
class IObserver;

// Base "Observable" interface
class IObservable
{
public:
    virtual ~IObservable() = default;
    virtual void subscribe(std::shared_ptr<IObserver> obs) = 0;
    virtual void unsubscribe(std::shared_ptr<IObserver> obs) = 0;
    virtual void notifyAll() = 0;
};

// Base "Observer" interface
class IObserver
{
public:
    virtual ~IObserver() = default;
    virtual void onUpdate() = 0;
};

// Concrete Observable: WeatherStation
class WeatherStation : public IObservable
{
private:
    std::vector<std::shared_ptr<IObserver>> observers_;
    int temperature_;

public:
    WeatherStation(int temp = 25) 
        : temperature_(temp)
    {
    }

    // IObservable interface implementations
    void subscribe(std::shared_ptr<IObserver> obs) override
    {
        observers_.push_back(obs);
    }

    void unsubscribe(std::shared_ptr<IObserver> obs) override
    {
        // Remove any matching observers
        observers_.erase(std::remove_if(observers_.begin(), observers_.end(),
            [&](const std::shared_ptr<IObserver>& o){
                return o == obs;
            }), observers_.end());
    }

    void notifyAll() override
    {
        for (auto& obs : observers_)
        {
            obs->onUpdate();
        }
    }

    // WeatherStation-specific
    int getTemperature() const
    {
        return temperature_;
    }

    void setTemperature(int newTemp)
    {
        temperature_ = newTemp;
        notifyAll(); 
    }
};

// Concrete Observer: PhoneDisplay
class PhoneDisplay : public IObserver
{
private:
    // We keep a shared_ptr to the WeatherStation so we can query it
    std::shared_ptr<WeatherStation> station_;

public:
    explicit PhoneDisplay(std::shared_ptr<WeatherStation> station)
        : station_(station)
    {
    }

    void onUpdate() override
    {
        if (station_)
        {
            std::cout << "[PhoneDisplay] Current temperature: "
                      << station_->getTemperature() << "°C\n";
        }
    }
};

// Concrete Observer: WindowDisplay
class WindowDisplay : public IObserver
{
private:
    std::shared_ptr<WeatherStation> station_;

public:
    explicit WindowDisplay(std::shared_ptr<WeatherStation> station)
        : station_(station)
    {
    }

    void onUpdate() override
    {
        if (station_)
        {
            std::cout << "[WindowDisplay] Current temperature: "
                      << station_->getTemperature() << "°C\n";
        }
    }
};

int main()
{
    // Create a shared WeatherStation
    auto station = std::make_shared<WeatherStation>(30);

    // Create two displays
    auto phone = std::make_shared<PhoneDisplay>(station);
    auto window = std::make_shared<WindowDisplay>(station);

    // Subscribe displays to the station
    station->subscribe(phone);
    station->subscribe(window);

    // Change temperature - triggers notifyAll()
    station->setTemperature(35);

    // Unsubscribe phone, only window display will react
    station->unsubscribe(phone);

    // Another temperature change
    station->setTemperature(40);

    return 0;
}
