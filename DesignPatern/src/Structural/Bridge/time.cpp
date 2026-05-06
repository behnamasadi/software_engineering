// Bridge — Time (abstraction) over TimeImp (implementation).
//
// `Time` defines what we can ask: tell me the time. `TimeImp` decides how
// it's formatted: 24h, civilian (AM/PM), or zoned. New time formats slot in
// as new TimeImp subclasses without changing Time or its callers.

#include <iomanip>
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

// Implementor.
class TimeImp {
public:
    TimeImp(int hr, int min) : hr_(hr), min_(min) {}
    virtual ~TimeImp() = default;

    virtual void tell() const {
        std::cout << "Time is " << std::setw(2) << std::setfill('0') << hr_
                  << ":" << std::setw(2) << std::setfill('0') << min_ << '\n';
    }

protected:
    int hr_, min_;
};

class CivilianTimeImp : public TimeImp {
public:
    CivilianTimeImp(int hr, int min, bool pm)
        : TimeImp(hr, min), suffix_(pm ? "PM" : "AM") {}

    void tell() const override {
        std::cout << "Time is " << hr_ << ":" << std::setw(2) << std::setfill('0')
                  << min_ << ' ' << suffix_ << '\n';
    }

private:
    std::string suffix_;
};

class ZuluTimeImp : public TimeImp {
public:
    ZuluTimeImp(int hr, int min, int zone) : TimeImp(hr, min) {
        switch (zone) {
            case 5: zone_ = "Eastern Standard Time"; break;
            case 6: zone_ = "Central Standard Time"; break;
            default: zone_ = "Unknown Time Zone"; break;
        }
    }

    void tell() const override {
        std::cout << "Time is " << std::setw(2) << std::setfill('0') << hr_
                  << ":" << std::setw(2) << std::setfill('0') << min_
                  << ' ' << zone_ << '\n';
    }

private:
    std::string zone_;
};

// Abstraction.
class Time {
public:
    virtual ~Time() = default;
    virtual void tell() const { imp_->tell(); }

protected:
    explicit Time(std::unique_ptr<TimeImp> imp) : imp_(std::move(imp)) {}

    std::unique_ptr<TimeImp> imp_;
};

class ConcreteTime : public Time {
public:
    ConcreteTime(int hr, int min)
        : Time(std::make_unique<TimeImp>(hr, min)) {}
};

class CivilianTime : public Time {
public:
    CivilianTime(int hr, int min, bool pm)
        : Time(std::make_unique<CivilianTimeImp>(hr, min, pm)) {}
};

class ZuluTime : public Time {
public:
    ZuluTime(int hr, int min, int zone)
        : Time(std::make_unique<ZuluTimeImp>(hr, min, zone)) {}
};

int main() {
    std::vector<std::unique_ptr<Time>> times;
    times.push_back(std::make_unique<ConcreteTime>(14, 30));
    times.push_back(std::make_unique<CivilianTime>(2, 30, true));
    times.push_back(std::make_unique<ZuluTime>(14, 30, 6));

    for (const auto& t : times) t->tell();
}
