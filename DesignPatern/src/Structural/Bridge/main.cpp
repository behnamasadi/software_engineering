#include <iostream>

using namespace std;

// Implementor
class RenderAPI {
public:
    virtual void renderSquare(double side) = 0;
    virtual ~RenderAPI() = default;
};

// Concrete Implementor A
class BrushRenderer : public RenderAPI {
public:
    void renderSquare(double side) override {
        cout << "\n[BrushRenderer] Rendering square with side = " << side << endl;
    }
};

// Concrete Implementor B
class PencilRenderer : public RenderAPI {
public:
    void renderSquare(double side) override {
        cout << "\n[PencilRenderer] Rendering square with side = " << side << endl;
    }
};

// Abstraction
class Shape {
public:
    virtual void display() = 0;  // Low-level
    virtual void scaleSize(double factor) = 0; // High-level
    virtual ~Shape() = default;
};

// Refined Abstraction
class Square : public Shape {
public:
    Square(double s, RenderAPI& renderer) : side(s), renderAPI(renderer) {}

    void display() override {
        renderAPI.renderSquare(side);
    }

    void scaleSize(double factor) override {
        side *= factor;
    }

private:
    double side;
    RenderAPI& renderAPI;
};

int main() {
    BrushRenderer brushRenderer;
    PencilRenderer pencilRenderer;

    Square squareA(1, brushRenderer);
    Square squareB(2, pencilRenderer);

    Shape* shapes[2] = { &squareA, &squareB };

    shapes[0]->scaleSize(10);
    shapes[0]->display();
    
    shapes[1]->scaleSize(10);
    shapes[1]->display();

    return 0;
}
