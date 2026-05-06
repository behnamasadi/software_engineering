// Decorator — start with a base court booking and stack add-ons (rackets,
// ball pack, coaching). Each add-on wraps a CourtBooking, forwards `cost()`
// to the wrapped booking, and adds its own charge.

#include <iostream>
#include <memory>
#include <utility>

class CourtBooking {
public:
    virtual ~CourtBooking() = default;
    virtual int cost() const = 0;
};

class GrassCourt : public CourtBooking {
public:
    int cost() const override {
        std::cout << "  grass court: 8000\n";
        return 8000;
    }
};

// Base decorator.
class TennisAddon : public CourtBooking {
public:
    explicit TennisAddon(std::unique_ptr<CourtBooking> court)
        : court_(std::move(court)) {}

protected:
    std::unique_ptr<CourtBooking> court_;
};

class CoachingAddon : public TennisAddon {
public:
    using TennisAddon::TennisAddon;
    int cost() const override {
        std::cout << "  coaching: 300\n";
        return court_->cost() + 300;
    }
};

class BallPackAddon : public TennisAddon {
public:
    using TennisAddon::TennisAddon;
    int cost() const override {
        std::cout << "  ball pack: 100\n";
        return court_->cost() + 100;
    }
};

class RacketAddon : public TennisAddon {
public:
    using TennisAddon::TennisAddon;
    int cost() const override {
        std::cout << "  rackets: 200\n";
        return court_->cost() + 200;
    }
};

int main() {
    std::cout << "Booking breakdown:\n";

    std::unique_ptr<CourtBooking> booking = std::make_unique<GrassCourt>();
    booking = std::make_unique<RacketAddon>(std::move(booking));
    booking = std::make_unique<BallPackAddon>(std::move(booking));
    booking = std::make_unique<CoachingAddon>(std::move(booking));

    int total = booking->cost();
    std::cout << "Total: " << total << '\n';
}
