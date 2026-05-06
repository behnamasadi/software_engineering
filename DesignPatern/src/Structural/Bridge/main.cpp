// Bridge — decouple an abstraction (Shape) from its implementation (RenderAPI).
//
// Without the Bridge: every (shape × renderer) combination becomes a class —
//   BrushSquare, PencilSquare, BrushCircle, PencilCircle, ...  N×M classes.
//
// With the Bridge: Shape holds a reference to a RenderAPI. Adding a new shape
// or a new renderer is independent — you do not multiply classes.

#include <iostream>
#include <memory>

// Implementor: knows how to draw primitives.
class RenderAPI {
public:
    virtual ~RenderAPI() = default;
    virtual void renderSquare(double side) = 0;
};

class BrushRenderer : public RenderAPI {
public:
    void renderSquare(double side) override {
        std::cout << "[Brush] square side=" << side << '\n';
    }
};

class PencilRenderer : public RenderAPI {
public:
    void renderSquare(double side) override {
        std::cout << "[Pencil] square side=" << side << '\n';
    }
};

// Abstraction: high-level shape API, delegates rendering to RenderAPI.
class Shape {
public:
    virtual ~Shape() = default;
    virtual void display() = 0;
    virtual void scaleSize(double factor) = 0;
};

class Square : public Shape {
public:
    Square(double side, RenderAPI& renderer)
        : side_(side), renderer_(renderer) {}

    void display() override { renderer_.renderSquare(side_); }
    void scaleSize(double factor) override { side_ *= factor; }

private:
    double side_;
    RenderAPI& renderer_;
};

int main() {
    BrushRenderer brush;
    PencilRenderer pencil;

    Square a(1, brush);
    Square b(2, pencil);

    a.scaleSize(10);
    a.display();

    b.scaleSize(10);
    b.display();
}
