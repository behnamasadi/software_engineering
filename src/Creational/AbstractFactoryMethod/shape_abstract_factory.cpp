#include <iostream>

using namespace std;
class Shape
{
public:
    Shape()
    {
        id_ = total_++;
    }

    virtual void draw() = 0;
protected:
    int id_;
    static int total_;
};

int Shape::total_ = 0;

class Circle : public Shape
{
public:
    void draw() {cout << "circle " << id_ << ": draw" << endl;}
};

class Square : public Shape
{
public:
    void draw()
    {
        cout << "square " << id_ << ": draw" << endl;
    }
};

class Ellipse : public Shape
{
public:
    void draw() {cout << "ellipse " << id_ << ": draw" << endl;}
};

class Rectangle : public Shape
{
public:
    void draw() {cout << "rectangle " << id_ << ": draw" << endl;}
};

class Factory
{
public:
    virtual Shape* createCurvedInstance() = 0;
    virtual Shape* createStraightInstance() = 0;
};

class SimpleShapeFactory : public Factory
{
public:
    Shape* createCurvedInstance()
    {
        return new Circle;
    }

    Shape* createStraightInstance()
    {
        return new Square;
    }
};

class RobustShapeFactory : public Factory
{
    public:
    Shape* createCurvedInstance()
    {
        return new Ellipse;
    }
    Shape* createStraightInstance()
    {
        return new Rectangle;
    }
};

#define SIMPLE=true
//#define ROBUST=true


int main()
{
    #ifdef SIMPLE
        Factory* factory = new SimpleShapeFactory;
    #elif ROBUST
        Factory* factory = new RobustShapeFactory;
    #endif
    Shape* shapes[3];

    shapes[0] = factory->createCurvedInstance();   // shapes[0] = new Ellipse;
    shapes[1] = factory->createStraightInstance(); // shapes[1] = new Rectangle;
    shapes[2] = factory->createCurvedInstance();   // shapes[2] = new Ellipse;

    for (int i=0; i < 3; i++)
    {
        shapes[i]->draw();
    }
}
