// Builder — assemble an Airplane piece by piece.
//
// Airplane          : the product
// AircraftBuilder   : abstract builder; one method per part
// JetBuilder/PropellerBuilder : concrete builders
// Director          : runs the same recipe regardless of builder

#include <iostream>
#include <memory>
#include <string>
#include <utility>

class Airplane {
public:
    explicit Airplane(std::string type) : type_(std::move(type)) {}

    void setBody(std::string body)     { body_   = std::move(body); }
    void setEngine(std::string engine) { engine_ = std::move(engine); }

    void describe() const {
        std::cout << "  " << type_ << " | body: " << body_ << " | engine: " << engine_ << '\n';
    }

private:
    std::string type_;
    std::string body_;
    std::string engine_;
};

class AircraftBuilder {
public:
    virtual ~AircraftBuilder() = default;

    virtual void start()       = 0;
    virtual void buildBody()   = 0;
    virtual void buildEngine() = 0;

    std::unique_ptr<Airplane> retrieve() { return std::move(airplane_); }

protected:
    std::unique_ptr<Airplane> airplane_;
};

class JetBuilder : public AircraftBuilder {
public:
    void start()       override { airplane_ = std::make_unique<Airplane>("Jet"); }
    void buildBody()   override { airplane_->setBody("aerodynamic jet body"); }
    void buildEngine() override { airplane_->setEngine("turbojet"); }
};

class PropellerBuilder : public AircraftBuilder {
public:
    void start()       override { airplane_ = std::make_unique<Airplane>("Propeller"); }
    void buildBody()   override { airplane_->setBody("lightweight body"); }
    void buildEngine() override { airplane_->setEngine("turboprop"); }
};

class Director {
public:
    std::unique_ptr<Airplane> construct(AircraftBuilder& builder) {
        builder.start();
        builder.buildBody();
        builder.buildEngine();
        return builder.retrieve();
    }
};

int main() {
    Director director;

    JetBuilder jet;
    director.construct(jet)->describe();

    PropellerBuilder prop;
    director.construct(prop)->describe();
}
