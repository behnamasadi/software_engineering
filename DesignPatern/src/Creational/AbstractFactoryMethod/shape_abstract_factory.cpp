// Abstract Factory — shape families.
// SimpleShapeFactory yields {Circle, Square}; RobustShapeFactory yields
// {Ellipse, Rectangle}. Client code only knows ShapeFactory and Shape.

#include <iostream>
#include <memory>
#include <vector>

class Shape {
public:
    Shape() : id_(total_++) {}
    virtual ~Shape() = default;
    virtual void draw() const = 0;

protected:
    int id_;

private:
    static int total_;
};
int Shape::total_ = 0;

class Circle : public Shape {
public:
    void draw() const override { std::cout << "  Circle "    << id_ << "\n"; }
};
class Square : public Shape {
public:
    void draw() const override { std::cout << "  Square "    << id_ << "\n"; }
};
class Ellipse : public Shape {
public:
    void draw() const override { std::cout << "  Ellipse "   << id_ << "\n"; }
};
class Rectangle : public Shape {
public:
    void draw() const override { std::cout << "  Rectangle " << id_ << "\n"; }
};

class ShapeFactory {
public:
    virtual ~ShapeFactory() = default;
    virtual std::unique_ptr<Shape> createCurvedShape()   = 0;
    virtual std::unique_ptr<Shape> createStraightShape() = 0;
};

class SimpleShapeFactory : public ShapeFactory {
public:
    std::unique_ptr<Shape> createCurvedShape()   override { return std::make_unique<Circle>(); }
    std::unique_ptr<Shape> createStraightShape() override { return std::make_unique<Square>(); }
};

class RobustShapeFactory : public ShapeFactory {
public:
    std::unique_ptr<Shape> createCurvedShape()   override { return std::make_unique<Ellipse>(); }
    std::unique_ptr<Shape> createStraightShape() override { return std::make_unique<Rectangle>(); }
};

void drawScene(ShapeFactory& factory) {
    std::vector<std::unique_ptr<Shape>> shapes;
    shapes.push_back(factory.createCurvedShape());
    shapes.push_back(factory.createStraightShape());
    shapes.push_back(factory.createCurvedShape());
    for (const auto& s : shapes) s->draw();
}

int main() {
    std::cout << "Simple family:\n";
    SimpleShapeFactory simple;
    drawScene(simple);

    std::cout << "Robust family:\n";
    RobustShapeFactory robust;
    drawScene(robust);
}
