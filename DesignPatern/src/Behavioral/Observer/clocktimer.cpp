#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <chrono>
#include <ctime>

// Forward declaration
class ITimeObserver;

// Base Observable
class ITimeObservable
{
public:
    virtual ~ITimeObservable() = default;

    // Register an observer
    virtual void addObserver(std::shared_ptr<ITimeObserver> obs) = 0;

    // Remove an observer
    virtual void removeObserver(std::shared_ptr<ITimeObserver> obs) = 0;

    // Notify all observers
    virtual void notifyObservers() = 0;
};

// Base Observer
class ITimeObserver
{
public:
    virtual ~ITimeObserver() = default;
    virtual void onTimeChange() = 0;
};

// Concrete Observable: ClockTicker
class ClockTicker : public ITimeObservable
{
private:
    std::vector<std::shared_ptr<ITimeObserver>> observers_;
    int hour_{0};
    int minute_{0};
    int second_{0};

public:
    ClockTicker()
    {
        // Initialize time to "now"
        updateCurrentTime();
    }

    void addObserver(std::shared_ptr<ITimeObserver> obs) override
    {
        observers_.push_back(obs);
    }

    void removeObserver(std::shared_ptr<ITimeObserver> obs) override
    {
        observers_.erase(std::remove_if(observers_.begin(), observers_.end(),
                                        [&](const std::shared_ptr<ITimeObserver>& ptr)
                                        {
                                            return ptr == obs;
                                        }),
                         observers_.end());
    }

    void notifyObservers() override
    {
        for (auto& obs : observers_)
        {
            obs->onTimeChange();
        }
    }

    // Update the internal time from the system clock (or any time source)
    void updateCurrentTime()
    {
        // Get the current system time
        auto now   = std::chrono::system_clock::now();
        std::time_t tt = std::chrono::system_clock::to_time_t(now);
        auto local = std::localtime(&tt);

        hour_   = local->tm_hour;
        minute_ = local->tm_min;
        second_ = local->tm_sec;

        // Whenever we update time, notify observers
        notifyObservers();
    }

    // Provide getters for hour, minute, second
    int getHour()   const { return hour_; }
    int getMinute() const { return minute_; }
    int getSecond() const { return second_; }
};

// Concrete Observer: DigitalView
class DigitalView : public ITimeObserver
{
private:
    // Keep a reference to the subject we observe
    std::shared_ptr<ClockTicker> ticker_;

public:
    explicit DigitalView(std::shared_ptr<ClockTicker> ticker)
        : ticker_(ticker)
    {
        if (ticker_)
        {
            ticker_->addObserver(std::shared_ptr<ITimeObserver>(this, [](ITimeObserver*) {
                // NOTE: We do nothing here in the custom deleter because
                // the actual lifetime is managed outside, or you can hold a
                // separate std::shared_ptr<DigitalView> if you prefer.
            }));
        }
    }

    // Called when the observable notifies
    void onTimeChange() override
    {
        if (!ticker_)
            return;

        std::cout << "[DigitalView] The time is: "
                  << ticker_->getHour() << ":"
                  << ticker_->getMinute() << ":"
                  << ticker_->getSecond()
                  << std::endl;
    }
};

// Concrete Observer: AnalogView
class AnalogView : public ITimeObserver
{
private:
    std::shared_ptr<ClockTicker> ticker_;

public:
    explicit AnalogView(std::shared_ptr<ClockTicker> ticker)
        : ticker_(ticker)
    {
        if (ticker_)
        {
            ticker_->addObserver(std::shared_ptr<ITimeObserver>(this, [](ITimeObserver*) {
                // Same note regarding custom deleter as above.
            }));
        }
    }

    void onTimeChange() override
    {
        if (!ticker_)
            return;

        std::cout << "[AnalogView] The time is: "
                  << ticker_->getHour() << ":"
                  << ticker_->getMinute() << ":"
                  << ticker_->getSecond()
                  << std::endl;
    }
};

int main()
{
    // Create a shared ClockTicker
    auto myClock = std::make_shared<ClockTicker>();

    // Create observer views
    auto digital = std::make_shared<DigitalView>(myClock);
    auto analog  = std::make_shared<AnalogView>(myClock);

    // Force an update to show the initial time
    myClock->updateCurrentTime();

    // Sleep or do some other operations, e.g. simulate next time change:
    // For example, let's pretend to increment the time manually:
    // (In real usage, you'd call updateCurrentTime() whenever time changes)
    // myClock->updateCurrentTime();

    // Remove the analog view if you want to stop updates
    myClock->removeObserver(analog);

    // Another time change to see only DigitalView's update
    myClock->updateCurrentTime();

    return 0;
}
