#include <iostream>

using namespace std;

// Implementor
class DrawingImplementor {
public:
    virtual void drawSquare(double) = 0;
 
    virtual ~DrawingImplementor() {
    }
};
 
// ConcreteImplementor A
class DrawingImplementorA: public DrawingImplementor {
public:
    DrawingImplementorA() {
    }
 
    virtual ~DrawingImplementorA() {
    }
 
	// example: drawing with brush
    void drawSquare(double side) {
        cout << "\nImplementorA.square with side = "<< side << endl;
    }
};
 
// ConcreteImplementor B
class DrawingImplementorB: public DrawingImplementor {
public:
    DrawingImplementorB() {
    }
 
    virtual ~DrawingImplementorB() {
    }
 
	// example: drawing with pencil
    void drawSquare(double side) {
        cout << "\nImplementorB.square with side = "<< side << endl;
    }
};

// Abstraction
class Shape {
public:
    virtual void draw()= 0; // low-level
    virtual void resize(double pct) = 0; // high-level
    virtual ~Shape() {
    }
};
 
// Refined Abstraction
class Square: public Shape {
public:
    Square(double s, DrawingImplementor& Implementor) : 
		side(s), drawingImplementor(Implementor) {
    }
 
    virtual ~Square() {
    }
 
    // low-level i.e. Implementation specific
    void draw() {
        drawingImplementor.drawSquare(side);
    }
    // high-level i.e. Abstraction specific
    void resize(double pct) {
        side *= pct;
    }
private:
    double side;
    DrawingImplementor& drawingImplementor;
};
 
int main(int argc, char* argv[]) {
    DrawingImplementorA ImplementorA;
    DrawingImplementorB ImplementorB;
 
    Square sqA(1, ImplementorA);
    Square sqB(2, ImplementorB);
 
    Shape* shapes[2];
    shapes[0] = &sqA;
    shapes[1] = &sqB;
 
    shapes[0]->resize(10);
    shapes[0]->draw();
    shapes[1]->resize(10);
    shapes[1]->draw();
 
    return 0;
}
