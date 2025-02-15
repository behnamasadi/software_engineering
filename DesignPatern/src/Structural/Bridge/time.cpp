//https://sourcemaking.com/design_patterns/bridge/cpp/1

#include <iostream>
#include <iomanip>
#include <memory>
#include <vector>
#include <string>

class TimeImp {
public:
    TimeImp(int hr, int min) : hr_(hr), min_(min) {}

    virtual void tell() const {
        std::cout << "Time is " << std::setw(2) << std::setfill('0') << hr_
                  << ":" << std::setw(2) << std::setfill('0') << min_ << std::endl;
    }

    virtual ~TimeImp() = default;

protected:
    int hr_, min_;
};

class CivilianTimeImp : public TimeImp {
public:
    CivilianTimeImp(int hr, int min, bool pm)
        : TimeImp(hr, min), whichM_(pm ? "PM" : "AM") {}

    void tell() const override {
        std::cout << "Time is " << hr_ << ":" << std::setw(2) << std::setfill('0')
                  << min_ << " " << whichM_ << std::endl;
    }

private:
    std::string whichM_;
};

class ZuluTimeImp : public TimeImp {
public:
    ZuluTimeImp(int hr, int min, int zone) : TimeImp(hr, min) {
        if (zone == 5)
            zone_ = "Eastern Standard Time";
        else if (zone == 6)
            zone_ = "Central Standard Time";
        else
            zone_ = "Unknown Time Zone";
    }

    void tell() const override {
        std::cout << "Time is " << std::setw(2) << std::setfill('0') << hr_
                  << ":" << std::setw(2) << std::setfill('0') << min_
                  << " " << zone_ << std::endl;
    }

private:
    std::string zone_;
};

class Time {
public:
    virtual void tell() const {
        imp_->tell();
    }

    virtual ~Time() = default;

protected:
    explicit Time(std::unique_ptr<TimeImp> imp) : imp_(std::move(imp)) {}

    std::unique_ptr<TimeImp> imp_;
};

// Concrete Implementation for a General Time
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
    
    // Use ConcreteTime instead of Time
    times.push_back(std::make_unique<ConcreteTime>(14, 30));
    times.push_back(std::make_unique<CivilianTime>(2, 30, true));
    times.push_back(std::make_unique<ZuluTime>(14, 30, 6));

    for (const auto& time : times)
        time->tell();

    return 0;
}
