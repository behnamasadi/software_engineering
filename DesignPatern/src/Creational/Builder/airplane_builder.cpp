#include <string>
#include <memory>
#include <iostream>

class Airplane
{
    std::string body;
    std::string engine;
    std::string type;
public:
    Airplane(std::string type):type(type){}

    void setBody(std::string body)
    {
        this->body=body;
    }

    void setEngine(std::string engine)
    {
        this->engine=engine;
    }

    std::string getBody()
    {
        return body;
    }

    std::string getEngine()
    {
        return engine;
    }

    void AirplaneInfo()
    {
        std::cout<<"Airplane type is: "<< type <<" body is: "<< body<<" engine is: " <<engine<<std::endl;
    }
};

class AirplaneBuilder
{
protected:
    Airplane * airplane;
public:
    Airplane * getPlane()
    {
        return airplane;
    }
    virtual void initializePlaneBuild()=0;
    virtual void buildBody()=0;
    virtual void buildEngine()=0;
};

class JetPlaneBuilder:public AirplaneBuilder
{
public:
    void initializePlaneBuild() override
    {
        airplane=new Airplane("Jet Plane");
    }
    void buildBody()override
    {
       airplane->setBody("Jet plane body");
    }
    void buildEngine()override
    {
        airplane->setEngine("Jet plane engine");
    }
};

class PropellerPlaneBuilder:public AirplaneBuilder
{
public:
    void initializePlaneBuild() override
    {
        airplane=new Airplane("Propeller Plane");
    }
    void buildBody()override
    {
       airplane->setBody("Propeller plane body");
    }
    void buildEngine()override
    {
        airplane->setEngine("Propeller plane engine");
    }
};

class Director
{
public:

    Airplane * createAirplane(AirplaneBuilder *builder)
    {
        builder->initializePlaneBuild();
        builder->buildBody();
        builder->buildEngine();
        return builder->getPlane();
    }

};

int main()
{
    JetPlaneBuilder *jetPlaneBuilderPtr=new JetPlaneBuilder;
    Director dir;
    Airplane * jetPlane= dir.createAirplane(jetPlaneBuilderPtr);
    jetPlane->AirplaneInfo();

    PropellerPlaneBuilder *propellerPlaneBuilderPtr=new PropellerPlaneBuilder;


    Airplane * propellerPlane= dir.createAirplane(propellerPlaneBuilderPtr);
    propellerPlane->AirplaneInfo();
}
