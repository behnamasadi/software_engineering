#include <iostream>
#include <memory>

using namespace std;

typedef int Coordinate;
typedef int Dimension;

// Desired interface
class Rectangle
{
public:
    virtual void display() = 0;
    virtual ~Rectangle() = default;
};

// Legacy component
class LegacyRectangle
{
public:
    LegacyRectangle(Coordinate x1, Coordinate y1, Coordinate x2, Coordinate y2)
        : x1_(x1), y1_(y1), x2_(x2), y2_(y2)
    {
        cout << "LegacyRectangle: created. (" << x1_ << "," << y1_ << ") => ("
             << x2_ << "," << y2_ << ")" << endl;
    }

    void renderOld()
    {
        cout << "LegacyRectangle: renderOld. (" << x1_ << "," << y1_
             << ") => (" << x2_ << "," << y2_ << ")" << endl;
    }

private:
    Coordinate x1_;
    Coordinate y1_;
    Coordinate x2_;
    Coordinate y2_;
};

// Adapter wrapper
class RectangleAdapter : public Rectangle, private LegacyRectangle
{
public:
    RectangleAdapter(Coordinate x, Coordinate y, Dimension w, Dimension h)
        : LegacyRectangle(x, y, x + w, y + h)
    {
        cout << "RectangleAdapter: created. (" << x << "," << y
             << "), width = " << w << ", height = " << h << endl;
    }

    void display() override
    {
        cout << "RectangleAdapter: display." << endl;
        renderOld();
    }
};

int main()
{
    Coordinate x1 = 120, y1 = 200;
    Dimension width = 60, height = 40;

    unique_ptr<Rectangle> r = make_unique<RectangleAdapter>(x1, y1, width, height);
    r->display();

    return 0;
}
