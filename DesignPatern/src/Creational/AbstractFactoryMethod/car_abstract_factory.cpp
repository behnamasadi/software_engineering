// Abstract Factory — regional car factories.
// IndiaCarFactory / USACarFactory / GlobalCarFactory each produce the same
// product family (Micro/Mini/Luxury) but stamped for their region.
// CarProductionHub picks the regional factory; client code asks for a model
// without knowing which factory backed it.

#include <iostream>
#include <memory>
#include <string>

enum class CarType { Micro, Mini, Luxury };
enum class Location { Default, USA, India };

const char* toString(CarType t) {
    switch (t) {
        case CarType::Micro:  return "Micro";
        case CarType::Mini:   return "Mini";
        case CarType::Luxury: return "Luxury";
    }
    return "?";
}

const char* toString(Location l) {
    switch (l) {
        case Location::Default: return "Default";
        case Location::USA:     return "USA";
        case Location::India:   return "India";
    }
    return "?";
}

class Car {
public:
    Car(CarType model, Location location) : model_(model), location_(location) {}
    virtual ~Car() = default;

    virtual void assemble() const = 0;

    std::string info() const {
        return std::string("model=") + toString(model_) + " location=" + toString(location_);
    }

private:
    CarType model_;
    Location location_;
};

class LuxuryCar : public Car {
public:
    explicit LuxuryCar(Location l) : Car(CarType::Luxury, l) {}
    void assemble() const override { std::cout << "  assembling luxury car\n"; }
};
class MicroCar : public Car {
public:
    explicit MicroCar(Location l) : Car(CarType::Micro, l) {}
    void assemble() const override { std::cout << "  assembling micro car\n"; }
};
class MiniCar : public Car {
public:
    explicit MiniCar(Location l) : Car(CarType::Mini, l) {}
    void assemble() const override { std::cout << "  assembling mini car\n"; }
};

class CarFactory {
public:
    virtual ~CarFactory() = default;
    virtual std::unique_ptr<Car> build(CarType type) const = 0;
};

class IndiaCarFactory : public CarFactory {
public:
    std::unique_ptr<Car> build(CarType type) const override {
        switch (type) {
            case CarType::Micro:  return std::make_unique<MicroCar>(Location::India);
            case CarType::Mini:   return std::make_unique<MiniCar>(Location::India);
            case CarType::Luxury: return std::make_unique<LuxuryCar>(Location::India);
        }
        return nullptr;
    }
};

class USACarFactory : public CarFactory {
public:
    std::unique_ptr<Car> build(CarType type) const override {
        switch (type) {
            case CarType::Micro:  return std::make_unique<MicroCar>(Location::USA);
            case CarType::Mini:   return std::make_unique<MiniCar>(Location::USA);
            case CarType::Luxury: return std::make_unique<LuxuryCar>(Location::USA);
        }
        return nullptr;
    }
};

class GlobalCarFactory : public CarFactory {
public:
    std::unique_ptr<Car> build(CarType type) const override {
        switch (type) {
            case CarType::Micro:  return std::make_unique<MicroCar>(Location::Default);
            case CarType::Mini:   return std::make_unique<MiniCar>(Location::Default);
            case CarType::Luxury: return std::make_unique<LuxuryCar>(Location::Default);
        }
        return nullptr;
    }
};

class CarProductionHub {
public:
    explicit CarProductionHub(Location region) {
        switch (region) {
            case Location::USA:   factory_ = std::make_unique<USACarFactory>();   break;
            case Location::India: factory_ = std::make_unique<IndiaCarFactory>(); break;
            default:              factory_ = std::make_unique<GlobalCarFactory>();
        }
    }

    std::unique_ptr<Car> build(CarType type) const { return factory_->build(type); }

private:
    std::unique_ptr<CarFactory> factory_;
};

int main() {
    CarProductionHub hub(Location::India);

    for (CarType t : {CarType::Micro, CarType::Mini, CarType::Luxury}) {
        auto car = hub.build(t);
        car->assemble();
        std::cout << "  -> " << car->info() << "\n\n";
    }
}
