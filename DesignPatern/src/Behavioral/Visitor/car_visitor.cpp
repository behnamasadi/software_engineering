#include <string>
#include <iostream>
#include <vector>

/*
The following example shows how the contents of a tree of nodes
(in this case describing the components of a car) can be printed.
Instead of creating print methods for each node subclass
(Wheel, Engine, Body, and Car), one visitor class (CarElementPrintVisitor)
performs the required printing action. Because different node subclasses
require slightly different actions to print properly, CarElementPrintVisitor
 dispatches actions based on the class of the argument passed to its visit method.
CarElementDoVisitor, which is analogous to a save operation for a different file
 format, does likewise.
*/





class CarElementVisitor;
class Body;
class Car;
class Engine;
class Wheel;


class CarElement
{
public:
    void virtual accept(CarElementVisitor *visitor){}
};

class CarElementVisitor
{
public:
    void virtual visit(Body *body)=0;
    void virtual visit(Car *car)=0;
    void virtual visit(Engine *engine)=0;
    void virtual visit(Wheel *wheel)=0;
};

class Wheel : public CarElement
{
private:
    std::string name;
public:
    Wheel(std::string name)
    {
        this->name = name;
    }

    std::string getName()
    {
        return name;
    }

    void accept(CarElementVisitor *visitor)
    {
      /*
       * accept(CarElementVisitor) in Wheel implements
       * accept(CarElementVisitor) in CarElement, so the call
       * to accept is bound at run time. This can be considered
       * the *first* dispatch. However, the decision to call
       * visit(Wheel) (as opposed to visit(Engine) etc.) can be
       * made during compile time since 'this' is known at compile
       * time to be a Wheel. Moreover, each implementation of
       * CarElementVisitor implements the visit(Wheel), which is
       * another decision that is made at run time. This can be
       * considered the *second* dispatch.
       */
      visitor->visit(this);
  }
};

class Body : public CarElement
{
    void accept(CarElementVisitor *visitor)
    {
        visitor->visit(this);
    }
};

class Engine : public CarElement
{
    void accept(CarElementVisitor *visitor)
    {
        visitor->visit(this);
    }
};

class Car : CarElement
{
private:
    std::vector<CarElement*> elements;

    public:
    Car()
    {
        this->elements = std::vector<CarElement*>{
            new Wheel("front left"), new Wheel("front right"),
            new Wheel("back left"), new Wheel("back right"),
            new Body(), new Engine()
        };
    }

public:
    void accept(CarElementVisitor *visitor)
    {
        for (CarElement* element : elements)
        {
            element->accept(visitor);
        }
        visitor->visit(this);
    }
};

class CarElementDoVisitor : public CarElementVisitor
{

public:
    void visit(Body *body)
    {
        std::cout<<"Moving my body"<<std::endl;
    }

    void visit(Car *car)
    {
        std::cout<<"Starting my car"<<std::endl;
    }

    void visit(Wheel *wheel)
    {
       std::cout<<"Kicking my " << wheel->getName() << " wheel"<<std::endl;
    }


    void visit(Engine *engine)
    {
        std::cout<<"Starting my engine"<<std::endl;
    }
};

class CarElementPrintVisitor : public CarElementVisitor
{
    void visit(Body *body)
    {
        std::cout<<"Visiting body"<<std::endl;
    }

    void visit(Car *car)
    {
        std::cout<<"Visiting car"<<std::endl;
    }

    void visit(Engine *engine)
    {
        std::cout<<"Visiting engine"<<std::endl;
    }

    void visit(Wheel *wheel)
    {
        std::cout<<"Visiting " << wheel->getName() << " wheel"<<std::endl;
    }
};

int  main()
{
    Car* car = new Car();
    car->accept(new CarElementPrintVisitor());
    car->accept(new CarElementDoVisitor());
}

