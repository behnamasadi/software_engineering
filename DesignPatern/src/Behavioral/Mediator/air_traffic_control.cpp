// Mediator — colleagues talk through a central object instead of to each other.
// Here, airplanes don't coordinate runway access among themselves; they ask
// the ATC tower, which keeps the rules in one place.

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

class Airplane;

class Mediator {
public:
    virtual ~Mediator() = default;
    virtual void requestLanding(Airplane& sender) = 0;
    virtual void requestTakeoff(Airplane& sender) = 0;
};

class Airplane {
public:
    Airplane(std::string name, Mediator& tower) : name_(std::move(name)), tower_(tower) {}

    const std::string& name() const { return name_; }

    void requestLanding() { tower_.requestLanding(*this); }
    void requestTakeoff() { tower_.requestTakeoff(*this); }

private:
    std::string name_;
    Mediator& tower_;
};

class ControlTower : public Mediator {
public:
    void parkOnGround(Airplane& plane) { ground_.push_back(&plane); }
    void putInAir(Airplane& plane)     { air_.push_back(&plane); }

    void requestLanding(Airplane& sender) override {
        std::cout << sender.name() << " requests landing\n";
        if (runwayBusy()) {
            std::cout << "  ATC: hold, runway occupied\n";
            return;
        }
        std::cout << "  ATC: cleared to land\n";
        move(&sender, air_, ground_);
    }

    void requestTakeoff(Airplane& sender) override {
        std::cout << sender.name() << " requests takeoff\n";
        if (runwayBusy()) {
            std::cout << "  ATC: hold, runway occupied\n";
            return;
        }
        std::cout << "  ATC: cleared for takeoff\n";
        move(&sender, ground_, air_);
    }

private:
    bool runwayBusy() const { return false; }  // simplified

    static void move(Airplane* p, std::vector<Airplane*>& from, std::vector<Airplane*>& to) {
        auto it = std::find(from.begin(), from.end(), p);
        if (it != from.end()) { from.erase(it); to.push_back(p); }
    }

    std::vector<Airplane*> air_;
    std::vector<Airplane*> ground_;
};

int main() {
    ControlTower tower;
    Airplane a("Flight A123", tower);
    Airplane b("Flight B456", tower);
    Airplane c("Flight C789", tower);

    tower.putInAir(a);
    tower.putInAir(b);
    tower.parkOnGround(c);

    a.requestLanding();
    c.requestTakeoff();
    b.requestLanding();
}
