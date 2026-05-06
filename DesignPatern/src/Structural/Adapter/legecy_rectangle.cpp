// Adapter — wrap a legacy class so it satisfies a new interface.
//
// The client wants to draw shapes through a `Rectangle` interface that takes
// (x, y, width, height) and offers `display()`. The legacy code only knows
// (x1, y1, x2, y2) and a `renderOld()` method we are not allowed to change.
//
// `RectangleAdapter` adapts the new (x, y, w, h) parameters to the legacy
// (x1, y1, x2, y2) form and exposes `display()` by delegating to `renderOld()`.

#include <iostream>
#include <memory>

// Desired (new) interface used by client code.
class Rectangle {
public:
    virtual ~Rectangle() = default;
    virtual void display() const = 0;
};

// Legacy component — assume we cannot modify it.
class LegacyRectangle {
public:
    LegacyRectangle(int x1, int y1, int x2, int y2)
        : x1_(x1), y1_(y1), x2_(x2), y2_(y2) {
        std::cout << "LegacyRectangle: created (" << x1_ << "," << y1_
                  << ") -> (" << x2_ << "," << y2_ << ")\n";
    }

    void renderOld() const {
        std::cout << "LegacyRectangle::renderOld (" << x1_ << "," << y1_
                  << ") -> (" << x2_ << "," << y2_ << ")\n";
    }

private:
    int x1_, y1_, x2_, y2_;
};

// Adapter: implements the new interface and delegates to the legacy class.
class RectangleAdapter : public Rectangle {
public:
    RectangleAdapter(int x, int y, int width, int height)
        : legacy_(x, y, x + width, y + height) {}

    void display() const override {
        std::cout << "RectangleAdapter::display -> ";
        legacy_.renderOld();
    }

private:
    LegacyRectangle legacy_;
};

int main() {
    std::unique_ptr<Rectangle> r =
        std::make_unique<RectangleAdapter>(120, 200, 60, 40);
    r->display();
}
