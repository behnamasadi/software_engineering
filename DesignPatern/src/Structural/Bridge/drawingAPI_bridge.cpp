#include <iostream>
#include <memory>

class DrawingAPI
{
public:
    virtual ~DrawingAPI() = default;
    virtual void renderCircle(double x, double y, double radius) = 0;
};

class DrawingAPIV1 : public DrawingAPI
{
public:
    void renderCircle(double x, double y, double radius) override
    {
        std::cout << "Rendering circle at x: " << x << ", y: " << y
                  << " with radius " << radius << " using API v1.0" << std::endl;
    }
};

class DrawingAPIV2 : public DrawingAPI
{
public:
    void renderCircle(double x, double y, double radius) override
    {
        std::cout << "Rendering circle at x: " << x << ", y: " << y
                  << " with radius " << radius << " using API v2.0" << std::endl;
    }
};

class Shape
{
public:
    virtual ~Shape() = default;
    virtual void display() = 0;
    virtual void scaleSize(double factor) = 0;
};

class CircleShape : public Shape
{
private:
    double m_x, m_y, m_radius;
    std::unique_ptr<DrawingAPI> m_drawingAPI;

public:
    CircleShape(double x, double y, double radius, std::unique_ptr<DrawingAPI> drawingAPI)
        : m_x(x), m_y(y), m_radius(radius), m_drawingAPI(std::move(drawingAPI)) {}

    void display() override
    {
        m_drawingAPI->renderCircle(m_x, m_y, m_radius);
    }

    void scaleSize(double factor) override
    {
        m_radius *= factor;
    }
};

int main()
{
    std::unique_ptr<Shape> circle1 = std::make_unique<CircleShape>(1, 2, 3, std::make_unique<DrawingAPIV1>());
    std::unique_ptr<Shape> circle2 = std::make_unique<CircleShape>(5, 7, 11, std::make_unique<DrawingAPIV2>());

    circle1->scaleSize(2.5);
    circle2->scaleSize(2.5);
    
    circle1->display();
    circle2->display();

    return 0;
}
