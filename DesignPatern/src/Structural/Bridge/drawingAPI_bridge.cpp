// Bridge — abstraction (Shape) over a swappable implementation (DrawingAPI).
//
// Two API versions, v1 and v2, draw circles. The CircleShape doesn't care
// which one — it just forwards to whatever DrawingAPI it was given. Adding a
// v3 means writing one new class; CircleShape stays untouched.

#include <iostream>
#include <memory>
#include <utility>

class DrawingAPI {
public:
    virtual ~DrawingAPI() = default;
    virtual void renderCircle(double x, double y, double radius) = 0;
};

class DrawingAPIV1 : public DrawingAPI {
public:
    void renderCircle(double x, double y, double r) override {
        std::cout << "API v1: circle at (" << x << "," << y << ") r=" << r << '\n';
    }
};

class DrawingAPIV2 : public DrawingAPI {
public:
    void renderCircle(double x, double y, double r) override {
        std::cout << "API v2: circle at (" << x << "," << y << ") r=" << r << '\n';
    }
};

class Shape {
public:
    virtual ~Shape() = default;
    virtual void display() = 0;
    virtual void scaleSize(double factor) = 0;
};

class CircleShape : public Shape {
public:
    CircleShape(double x, double y, double radius, std::unique_ptr<DrawingAPI> api)
        : x_(x), y_(y), radius_(radius), api_(std::move(api)) {}

    void display() override { api_->renderCircle(x_, y_, radius_); }
    void scaleSize(double factor) override { radius_ *= factor; }

private:
    double x_, y_, radius_;
    std::unique_ptr<DrawingAPI> api_;
};

int main() {
    std::unique_ptr<Shape> circle1 =
        std::make_unique<CircleShape>(1, 2, 3, std::make_unique<DrawingAPIV1>());
    std::unique_ptr<Shape> circle2 =
        std::make_unique<CircleShape>(5, 7, 11, std::make_unique<DrawingAPIV2>());

    circle1->scaleSize(2.5);
    circle2->scaleSize(2.5);

    circle1->display();
    circle2->display();
}
