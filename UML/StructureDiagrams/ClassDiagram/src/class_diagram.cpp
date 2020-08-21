#include <string>
#include <vector>
#include <iostream>
#include <functional>
using namespace std;

/////////////////////////////////////////// class diagram ///////////////////////////////////////////

/*
,--------------------------.
|Animal                    |
|--------------------------|
|-name:string              |
|#id: int                  |
|--------------------------|
|+setName(string name):void|
|+move(): void             |
|+count(): int             |
`--------------------------'

*/

class Animal
{
private:
	string name;
protected:
	int id;
public:
	void setName(string name) {}
	void virtual move() {}
	static int count() {}
};

/////////////////////////////////////////// Composition ///////////////////////////////////////////
namespace Composition
{


class Point
{
};

class Circle
{
private:
	Point center;
};


class Heart
{
};

class Person
{
private:
	Heart heart;
};


class File
{

};
class Folder
{
public:
    vector<File> files;
};


class Departments
{

};

class Hospital
{
public:
    Hospital(int n) { departments = new Departments[n]; }
    ~Hospital(){ delete [] departments; }
    Departments *departments; // 0..*; Composition
};
}

/////////////////////////////////////////// Aggregation ///////////////////////////////////////////

namespace Aggregation
{
class Proffesor
{
private:
    std::string m_name;
public:
    Proffesor(std::string name): m_name(name) { }
    std::string getName() { return m_name; }
};

class Department
{
private:
    std::vector<std::reference_wrapper<const Proffesor>>  m_proffesors;

public:

    void addProffesor(const Proffesor& proffesor )
    {
        m_proffesors.push_back(proffesor);
    }
};
}

/////////////////////////////////////////// Association ///////////////////////////////////////////

namespace Association
{
class Student;

class Teacher
{
private:
    std::vector<std::reference_wrapper<const Student>> m_students{};

public:
    void addStudent(Student& student);

};

class Student
{
    std::vector<std::reference_wrapper<const Teacher>> m_teacher{};
public:
    void addTeacher(const Teacher& teacher)
    {
        m_teacher.push_back(teacher);
    }
};

}


/////////////////////////////////////////// Dependency ///////////////////////////////////////////

class Y
{
public:
    void foo(){}
    void static StaticFoo(){}
};
class X
{
    void f1(Y y)  {y.foo();       }
    void f2(Y *y) {y->foo();      }
    void f3(Y &y) {y.foo();       }
    void f4()     {Y y; y.foo();}
    void f5()     {Y::StaticFoo(); }
};


/////////////////////////////////////////// Inheritance ///////////////////////////////////////////

namespace Inheritance
{
class Shape
{
public:
    void virtual draw();
    double virtual getArea();
};

class Circle: public Shape
{
    void draw() override{}
    double getArea() override{}
};

class Ellipse : public Shape
{
    void draw() override{}
    double getArea() override{}
};
}

/////////////////////////////////////////// Template ///////////////////////////////////////////

namespace Template
{

template <class T>
class Foo{T item;} ;
Foo<int> fooInt;
Foo<double> fooFouble;
}

int main() 
{
    Aggregation::Proffesor Bob("Bob");
    Aggregation::Proffesor Jim("Jim");
    {
        Aggregation::Department dept;
        dept.addProffesor(Bob);
        dept.addProffesor(Jim);
    }
    std::cout << Bob.getName() << " still exists!";
    std::cout << Jim.getName() << " still exists!";


    return 0;
}
