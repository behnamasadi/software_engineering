#include <memory>
#include <iostream>
#include <string>

// Base class for court booking
class CourtBooking
{
public:
    virtual int cost() const
    {
        return 1000;  // Base price
    }

    virtual ~CourtBooking() = default; // Ensures proper polymorphic destruction
};

// Abstract Decorator Class
class TennisAddon : public CourtBooking
{
protected:
    std::unique_ptr<CourtBooking> court;

public:
    explicit TennisAddon(std::unique_ptr<CourtBooking> cb) : court(std::move(cb)) {}

    virtual int cost() const override = 0; // Ensure derived classes implement this
};

// Concrete Grass Court Booking
class GrassCourt : public CourtBooking
{
public:
    int cost() const override
    {
        std::cout << "Grass Court Booking: 8000" << std::endl;
        return 8000;
    }
};

// Concrete Decorator - Coaching
class CoachingAddon : public TennisAddon
{
public:
    explicit CoachingAddon(std::unique_ptr<CourtBooking> cb) : TennisAddon(std::move(cb)) {}

    int cost() const override
    {
        std::cout << "Coaching cost: 300" << std::endl;
        return court->cost() + 300;
    }
};

// Concrete Decorator - Ball Pack
class BallPackAddon : public TennisAddon
{
public:
    explicit BallPackAddon(std::unique_ptr<CourtBooking> cb) : TennisAddon(std::move(cb)) {}

    int cost() const override
    {
        std::cout << "Ball Pack cost: 100" << std::endl;
        return court->cost() + 100;
    }
};

// Concrete Decorator - Rackets
class RacketAddon : public TennisAddon
{
public:
    explicit RacketAddon(std::unique_ptr<CourtBooking> cb) : TennisAddon(std::move(cb)) {}

    int cost() const override
    {
        std::cout << "Rackets cost: 200" << std::endl;
        return court->cost() + 200;
    }
};

int main()
{
    std::cout << "Booking Details and Costs:\n";

    // Base grass court booking
    std::unique_ptr<CourtBooking> booking = std::make_unique<GrassCourt>();

    // Add-ons
    booking = std::make_unique<RacketAddon>(std::move(booking));
    booking = std::make_unique<BallPackAddon>(std::move(booking));
    booking = std::make_unique<CoachingAddon>(std::move(booking));

    // Final cost calculation
    std::cout << "Total Cost: " << booking->cost() << std::endl;

    return 0;
}
