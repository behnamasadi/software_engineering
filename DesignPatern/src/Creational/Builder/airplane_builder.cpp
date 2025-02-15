#include <string>
#include <memory>
#include <iostream>

// Airplane class
class Airplane
{
    std::string body;
    std::string engine;
    std::string type;

public:
    explicit Airplane(std::string type) : type(std::move(type)) {}

    void setBody(const std::string& body) { this->body = body; }
    void setEngine(const std::string& engine) { this->engine = engine; }

    std::string getBody() const { return body; }
    std::string getEngine() const { return engine; }

    void displayInfo() const
    {
        std::cout << "✈️ Airplane Type: " << type
                  << " | Body: " << body
                  << " | Engine: " << engine << std::endl;
    }
};

// Abstract Builder
class AircraftBuilder
{
protected:
    std::unique_ptr<Airplane> airplane;

public:
    virtual ~AircraftBuilder() = default;

    std::unique_ptr<Airplane> getPlane()
    {
        return std::move(airplane);
    }

    virtual void startConstruction() = 0;
    virtual void buildBody() = 0;
    virtual void buildEngine() = 0;
};

// Concrete Builder: Jet Plane
class JetBuilder : public AircraftBuilder
{
public:
    void startConstruction() override
    {
        airplane = std::make_unique<Airplane>("Jet Plane");
    }

    void buildBody() override
    {
        airplane->setBody("Sleek aerodynamic jet body");
    }

    void buildEngine() override
    {
        airplane->setEngine("High-thrust turbojet engine");
    }
};

// Concrete Builder: Propeller Plane
class PropellerBuilder : public AircraftBuilder
{
public:
    void startConstruction() override
    {
        airplane = std::make_unique<Airplane>("Propeller Plane");
    }

    void buildBody() override
    {
        airplane->setBody("Durable lightweight propeller body");
    }

    void buildEngine() override
    {
        airplane->setEngine("Efficient turboprop engine");
    }
};

// Director class
class Director
{
public:
    std::unique_ptr<Airplane> constructAirplane(AircraftBuilder& builder)
    {
        builder.startConstruction();
        builder.buildBody();
        builder.buildEngine();
        return builder.getPlane();
    }
};

// Main function
int main()
{
    Director director;

    // Build a Jet Plane
    JetBuilder jetBuilder;
    std::unique_ptr<Airplane> jetPlane = director.constructAirplane(jetBuilder);
    jetPlane->displayInfo();

    // Build a Propeller Plane
    PropellerBuilder propellerBuilder;
    std::unique_ptr<Airplane> propellerPlane = director.constructAirplane(propellerBuilder);
    propellerPlane->displayInfo();

    return 0;
}
