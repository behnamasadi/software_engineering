#include <iostream>
#include <memory>
#include <vector>

using namespace std;

class Shape
{
protected:
    int id_;
    static int total_;

public:
    Shape() : id_(total_++) {}
    virtual void draw() = 0;
    virtual ~Shape() = default;
};

int Shape::total_ = 0;

class Circle : public Shape
{
public:
    void draw() override { cout << "⭕ Circle " << id_ << ": draw" << endl; }
};

class Square : public Shape
{
public:
    void draw() override { cout << "⬜ Square " << id_ << ": draw" << endl; }
};

class Ellipse : public Shape
{
public:
    void draw() override { cout << "🟢 Ellipse " << id_ << ": draw" << endl; }
};

class Rectangle : public Shape
{
public:
    void draw() override { cout << "🟦 Rectangle " << id_ << ": draw" << endl; }
};

// Abstract Factory
class ShapeFactory
{
public:
    virtual unique_ptr<Shape> createCurvedShape() = 0;
    virtual unique_ptr<Shape> createStraightShape() = 0;
    virtual ~ShapeFactory() = default;
};

// Simple Shape Factory
class SimpleShapeFactory : public ShapeFactory
{
public:
    unique_ptr<Shape> createCurvedShape() override
    {
        return make_unique<Circle>();
    }

    unique_ptr<Shape> createStraightShape() override
    {
        return make_unique<Square>();
    }
};

// Robust Shape Factory
class RobustShapeFactory : public ShapeFactory
{
public:
    unique_ptr<Shape> createCurvedShape() override
    {
        return make_unique<Ellipse>();
    }

    unique_ptr<Shape> createStraightShape() override
    {
        return make_unique<Rectangle>();
    }
};

// Define which factory to use
#define SIMPLE_FACTORY  // Change to ROBUST_FACTORY to switch

int main()
{
    unique_ptr<ShapeFactory> factory;

#ifdef SIMPLE_FACTORY
    factory = make_unique<SimpleShapeFactory>();
#elif defined(ROBUST_FACTORY)
    factory = make_unique<RobustShapeFactory>();
#endif

    vector<unique_ptr<Shape>> shapes;

    // Create different types of shapes using factory
    shapes.push_back(factory->createCurvedShape());   // Circle or Ellipse
    shapes.push_back(factory->createStraightShape()); // Square or Rectangle
    shapes.push_back(factory->createCurvedShape());   // Circle or Ellipse

    // Draw all shapes
    for (const auto& shape : shapes)
    {
        shape->draw();
    }

    return 0;
}
