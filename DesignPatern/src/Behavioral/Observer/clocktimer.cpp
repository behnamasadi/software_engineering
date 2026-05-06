// Observer — clock variant.
// A clock notifies all attached views whenever the time advances. Views read
// the current time from the subject (pull model).

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>

class Clock;

class TimeView {
public:
    virtual ~TimeView() = default;
    virtual void onTimeChanged(const Clock& clock) = 0;
};

class Clock {
public:
    void attach(TimeView& v) { views_.push_back(&v); }
    void detach(TimeView& v) {
        views_.erase(std::remove(views_.begin(), views_.end(), &v), views_.end());
    }

    int hour()   const { return h_; }
    int minute() const { return m_; }
    int second() const { return s_; }

    void tick() {
        if (++s_ == 60) { s_ = 0; if (++m_ == 60) { m_ = 0; ++h_; } }
        for (auto* v : views_) v->onTimeChanged(*this);
    }

private:
    int h_ = 11, m_ = 59, s_ = 58;
    std::vector<TimeView*> views_;
};

class DigitalView : public TimeView {
public:
    void onTimeChanged(const Clock& c) override {
        std::cout << "[digital] " << std::setfill('0')
                  << std::setw(2) << c.hour()   << ':'
                  << std::setw(2) << c.minute() << ':'
                  << std::setw(2) << c.second() << '\n';
    }
};

class AnalogView : public TimeView {
public:
    void onTimeChanged(const Clock& c) override {
        std::cout << "[analog]  hour-hand at " << c.hour() % 12 << '\n';
    }
};

int main() {
    Clock clock;
    DigitalView digital;
    AnalogView analog;

    clock.attach(digital);
    clock.attach(analog);

    for (int i = 0; i < 4; ++i) clock.tick();
    clock.detach(analog);
    clock.tick();
}
