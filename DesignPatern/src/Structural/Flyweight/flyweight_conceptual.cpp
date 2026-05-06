// Flyweight — share the heavy, repeated part of an object across many
// instances. Each car has shared (intrinsic) state that varies a little —
// brand, model, color — and unique (extrinsic) state that varies a lot —
// owner, plates. Storing one Flyweight per (brand, model, color) combination
// lets the factory hand out the same shared instance instead of duplicating
// it for every car record.

#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>

// Intrinsic state — shared.
struct SharedState {
    std::string brand;
    std::string model;
    std::string color;

    friend std::ostream& operator<<(std::ostream& os, const SharedState& s) {
        return os << "[" << s.brand << ", " << s.model << ", " << s.color << "]";
    }
};

// Extrinsic state — passed in by the client at use time.
struct UniqueState {
    std::string owner;
    std::string plates;

    friend std::ostream& operator<<(std::ostream& os, const UniqueState& u) {
        return os << "[" << u.owner << ", " << u.plates << "]";
    }
};

class Flyweight {
public:
    explicit Flyweight(SharedState shared) : shared_(std::move(shared)) {}

    void display(const UniqueState& unique) const {
        std::cout << "  shared=" << shared_ << " unique=" << unique << '\n';
    }

private:
    SharedState shared_;
};

class FlyweightFactory {
public:
    FlyweightFactory(std::initializer_list<SharedState> shared_states) {
        for (const auto& s : shared_states) flyweights_.emplace(key(s), Flyweight(s));
    }

    const Flyweight& get(const SharedState& s) {
        auto k = key(s);
        auto it = flyweights_.find(k);
        if (it != flyweights_.end()) {
            std::cout << "Factory: reusing flyweight " << k << '\n';
            return it->second;
        }
        std::cout << "Factory: creating flyweight " << k << '\n';
        return flyweights_.emplace(k, Flyweight(s)).first->second;
    }

    void list() const {
        std::cout << "Factory has " << flyweights_.size() << " flyweights:\n";
        for (const auto& [k, _] : flyweights_) std::cout << "  - " << k << '\n';
    }

private:
    static std::string key(const SharedState& s) {
        return s.brand + "_" + s.model + "_" + s.color;
    }

    std::unordered_map<std::string, Flyweight> flyweights_;
};

void addCar(FlyweightFactory& factory,
            const std::string& plates, const std::string& owner,
            const std::string& brand, const std::string& model,
            const std::string& color) {
    std::cout << "Client: adding car " << plates << '\n';
    factory.get({brand, model, color}).display({owner, plates});
}

int main() {
    FlyweightFactory factory{
        {"Chevrolet", "Camaro2018", "pink"},
        {"Mercedes Benz", "C300", "black"},
        {"Mercedes Benz", "C500", "red"},
        {"BMW", "M5", "red"},
        {"BMW", "X6", "white"}};

    factory.list();

    addCar(factory, "CL234IR", "James Doe", "BMW", "M5", "red");
    addCar(factory, "XY567AB", "Alice Johnson", "BMW", "X1", "red");

    factory.list();
}
