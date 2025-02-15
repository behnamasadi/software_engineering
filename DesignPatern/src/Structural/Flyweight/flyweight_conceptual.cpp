#include <iostream>
#include <unordered_map>
#include <memory>

// Common state (Intrinsic)
struct SharedState
{
    std::string brand_;
    std::string model_;
    std::string color_;

    SharedState(std::string brand, std::string model, std::string color)
        : brand_(std::move(brand)), model_(std::move(model)), color_(std::move(color))
    {
    }

    friend std::ostream& operator<<(std::ostream& os, const SharedState& ss)
    {
        return os << "[ " << ss.brand_ << " , " << ss.model_ << " , " << ss.color_ << " ]";
    }
};

// Unique state (Extrinsic)
struct UniqueState
{
    std::string owner_;
    std::string plates_;

    UniqueState(std::string owner, std::string plates)
        : owner_(std::move(owner)), plates_(std::move(plates))
    {
    }

    friend std::ostream& operator<<(std::ostream& os, const UniqueState& us)
    {
        return os << "[ " << us.owner_ << " , " << us.plates_ << " ]";
    }
};

// The Flyweight class stores intrinsic state
class Flyweight
{
private:
    std::shared_ptr<SharedState> shared_state_; // Use shared_ptr for shared objects

public:
    explicit Flyweight(std::shared_ptr<SharedState> shared_state)
        : shared_state_(std::move(shared_state))
    {
    }

    void DisplayInfo(const UniqueState& unique_state) const
    {
        std::cout << "🚗 Flyweight: Displaying shared (" << *shared_state_ 
                  << ") and unique (" << unique_state << ") state.\n";
    }

    std::shared_ptr<SharedState> getSharedState() const
    {
        return shared_state_;
    }
};

// The Flyweight Factory creates and manages flyweight objects
class FlyweightFactory
{
private:
    std::unordered_map<std::string, std::shared_ptr<Flyweight>> flyweights_;

    std::string GetKey(const SharedState& ss) const
    {
        return ss.brand_ + "_" + ss.model_ + "_" + ss.color_;
    }

public:
    FlyweightFactory(std::initializer_list<SharedState> shared_states)
    {
        for (const auto& ss : shared_states)
        {
            flyweights_.emplace(GetKey(ss), std::make_shared<Flyweight>(std::make_shared<SharedState>(ss)));
        }
    }

    std::shared_ptr<Flyweight> FindOrCreateFlyweight(const SharedState& shared_state)
    {
        std::string key = GetKey(shared_state);
        auto it = flyweights_.find(key);

        if (it == flyweights_.end())
        {
            std::cout << "⚠️ FlyweightFactory: Creating new flyweight.\n";
            auto flyweight = std::make_shared<Flyweight>(std::make_shared<SharedState>(shared_state));
            flyweights_[key] = flyweight;
            return flyweight;
        }
        else
        {
            std::cout << "✅ FlyweightFactory: Reusing existing flyweight.\n";
            return it->second;
        }
    }

    void ListFlyweights() const
    {
        std::cout << "\n📌 FlyweightFactory: Total " << flyweights_.size() << " flyweights:\n";
        for (const auto& pair : flyweights_)
        {
            std::cout << "   - " << pair.first << "\n";
        }
    }
};

// Simulating a client adding a car to a database
void AddCarToDatabase(
    FlyweightFactory& factory, const std::string& plates, const std::string& owner,
    const std::string& brand, const std::string& model, const std::string& color)
{
    std::cout << "\n🔍 Client: Adding a new car entry to the database...\n";
    auto flyweight = factory.FindOrCreateFlyweight({ brand, model, color });
    flyweight->DisplayInfo({ owner, plates });
}

// Main execution
int main()
{
    auto factory = std::make_shared<FlyweightFactory>(
        std::initializer_list<SharedState>{
            {"Chevrolet", "Camaro2018", "pink"},
            {"Mercedes Benz", "C300", "black"},
            {"Mercedes Benz", "C500", "red"},
            {"BMW", "M5", "red"},
            {"BMW", "X6", "white"} });

    factory->ListFlyweights();

    // Adding cars to the database
    AddCarToDatabase(*factory, "CL234IR", "James Doe", "BMW", "M5", "red");
    AddCarToDatabase(*factory, "XY567AB", "Alice Johnson", "BMW", "X1", "red");

    factory->ListFlyweights(); // Check if new flyweights were added

    return 0;
}
