#include <iostream>

class DrawingAPI
{
public:
    virtual void drawCircle(double x, double y, double radius)=0;
};

class DrawingAPIV1 : public DrawingAPI
{
public:
    void drawCircle(double x, double y, double radius) override
    {
        std::cout<<"drawing circle at"<<"x: "<<x <<" y: "<<y <<" with radius "<<radius<<" API version 1.0" <<std::endl;
    }
};

class DrawingAPIV2 : public DrawingAPI
{
public:
    void drawCircle(double x, double y, double radius) override
    {
        std::cout<<"drawing circle at"<<"x: "<<x <<" y: "<<y <<" with radius "<<radius<<" API version 2.0" <<std::endl;
    }
};



class Shape
{
public:
    virtual ~Shape() {}
    virtual void draw() = 0;
    virtual void resizeByPercentage(double pct) = 0;
};

class CircleShape : public Shape
{
private:
    double m_x, m_y, m_radius;
    DrawingAPI *m_drawingAPI;

public:
    CircleShape(double x, double y,double radius, DrawingAPI *drawingAPI) :
    m_x(x), m_y(y), m_radius(radius), m_drawingAPI(drawingAPI) {}

    void draw()
    {
        m_drawingAPI->drawCircle(m_x, m_y, m_radius);
    }
    void resizeByPercentage(double pct)
    {
        m_radius *= pct;
    }
};



int main()
{
    CircleShape circle1(1,2,3,new DrawingAPIV1());
    CircleShape circle2(5,7,11,new DrawingAPIV2());
    circle1.resizeByPercentage(2.5);
    circle2.resizeByPercentage(2.5);
    circle1.draw();
    circle2.draw();
}
