/*
Tutorial here has been acquired from:
https://cppcodetips.wordpress.com/2013/12/23/uml-class-diagram-explained-with-c-samples/


https://www.learncpp.com/
(Chapter 10)

ASCII chars:
https://www.alt-codes.net/
► ◄ ▲ ▼ ◆ ◇ ♦ △ ▽ ◁ ▷ ◹ ◸ ◺ ◿

𝗕𝗼𝗹𝗱/𝐼𝑡𝑎𝑙𝑖𝑐,u͟n͟d͟e͟r͟l͟i͟n͟e͟
https://yaytext.com/

I)A class representation

class Circle
{
private:
    double radius;
    Point center;
public:
    setRadius(double radius);
    setCenter(Point center);
    double getArea();
    double getCircumfrence();
};


Class diagram for the above class is shown below.

_________________________________
|            circle             |
|-------------------------------|
|-radius: double                |
|-center: Point                 |
|-------------------------------|
|setRadius(double:radius):void  |
|setCenter(Point:center):void   |
|getArea(void):double           |
|getCircumfrence(void):double   |
|_______________________________|

Different type of members in a class
1) S͟t͟a͟t͟i͟c͟ ͟m͟e͟m͟b͟e͟r͟s͟ are represented as underlined.
2) 𝘗𝘶𝘳𝘦 𝘷𝘪𝘳𝘵𝘶𝘢𝘭 functions are represented as italics.


II)Class relationship

In a system a class may be related to different classes,following are the different relation ship.

1)Association (knows a, Uses-a) ------->
2)Dependency (uses a) - - - - - ->
3)Aggregation (has a) ◇------------->
4)Composition (has a) ◆------------->
5)Inheritance (is a) ----------▷
6)Class template

Different Multiplicity in a relation
“0..1”            No instances, or one instance (optional, may)
“1”                  Exactly one instance
“0..* or *”    Zero or more instances
“1..*”              One or more instances (at least one)


In nutshell:
Association is a pointer to an other class and life cycle doesn't depend on the class.
Aggregation is vague concept and could be similar to Association.
Dependency is done via sending an object via function parameter.
Composition is when a class has member of an other class and maintains the life cycle.

////////////////////////////////////////////(1)Association////////////////////////////////////////////
To qualify as an association, an object and another object must have the following relationship:

The associated object (member) is otherwise unrelated to the object (class)
The associated object (member) can belong to more than one object (class) at a time
The associated object (member) does not have its existence managed by the object (class)
The associated object (member) may or may not know about the existence of the object (class)
Because associations are a broad type of relationship, they can be implemented in many different ways.
However, most often, associations are implemented using pointers, where the object points at the associated object.



Representaion

Class X
{
    X(Y *y) : y_ptr(y) {}
    void SetY(Y *y) { y_ptr = y;   }
    void f()        { y_ptr->Foo();}
    ----
    Y *y_ptr; // pointer
};

_______________        _______________
|       X     |        |     Y       |
|-------------|------->|-------------|
|-------------|        |-------------|
|_____________|        |_____________|




////////////////////////////////////////////(2)Dependency////////////////////////////////////////////
One class depends on another if the independent class is a parameter variable or
local variable of a method of the dependent class

class X {
 ...
 void f1(Y y)  {…;  y.Foo();       }
 void f2(Y *y) {…;  y->Foo();      }
 void f3(Y &y) {…;  y.Foo();       }
 void f4()     {   Y y; y.Foo();  …}
 void f5()     {…; Y::StaticFoo(); }
};

_______________            _______________
|       X     |            |     Y       |
|-------------|- - - - - ->|-------------|
|-------------|            |-------------|
|_____________|            |_____________|




////////////////////////////////////////////(3)Aggregation////////////////////////////////////////////
Aggregation can occur when a class is a collection or container of other classes, but where the contained classes
do not have a strong life cycle dependency on the container—essentially, if the container is destroyed,
its contents are not. You may have confusion between aggregation and association.
Association differs from aggregation only in that it does not imply any containment.

To qualify as an aggregation, a whole object and its parts must have the following relationship:

The part (member) is part of the object (class)
The part (member) can belong to more than one object (class) at a time
The part (member) does not have its existence managed by the object (class)
The part (member) does not know about the existence of the object (class)

class Teacher
{
private:
    std::string m_name;
public:
    Teacher(std::string name): m_name(name) { }
    std::string getName() { return m_name; }
};


class Department
{
private:
    Teacher *m_teacher; // This dept holds only one teacher for simplicity, but it could hold many teachers
public:
    Department(Teacher *teacher = nullptr): m_teacher(teacher){}
};


_______________               _______________
| Department  | -m_teacher    |   Teacher   |
|-------------|◇------------->|-------------|
|-------------|              1|-------------|
|_____________|               |_____________|

A department has a teacher, and the scope of teacher doesn’t depend on the department since a teacher can be
member of another department.

int main()
{
    Teacher *teacher = new Teacher("Bob"); // create a teacher
    {
        Department dept(teacher);
    }
    // Teacher still exists here because dept did not delete m_teacher
    std::cout << teacher->getName() << " still exists!";
    delete teacher;
    return 0;
}


////////////////////////////////////////////(4)Composition////////////////////////////////////////////
Composition is the stronger form of aggregation. Composition can occur when a class is a collection or container of other classes,
but where the contained classes have a strong life cycle dependency on the container—essentially, if the container is destroyed,
its contents are also destroyed.

To qualify as a composition, an object and a part must have the following relationship:

The part (member) is part of the object (class)
The part (member) can only belong to one object (class) at a time
The part (member) has its existence managed by the object (class)
The part (member) does not know about the existence of the object (class)

Compositions are one of the easiest relationship types to implement in C++.
They are typically created as structs or classes with normal data members.
Because these data members exist directly as part of the struct/class, their lifetimes are bound to that
of the class instance itself. Compositions that need to do dynamic allocation or deallocation may be
implemented using pointer data members. In this case, the composition class should be responsible for
doing all necessary memory management itself (not the user of the class).



Composition vs Aggregation
Because aggregations are similar to compositions in that they are both part-whole relationships,
they are implemented almost identically, and the difference between them is mostly semantic.
In a composition, we typically add our parts to the composition using normal member variables
(or pointers where the allocation and deallocation process is handled by the composition class).
In an aggregation, we also add parts as member variables. However, these member variables are typically either
references or pointers that are used to point at objects that have been created outside the scope of the class.
Consequently, an aggregation usually either takes the objects it is going to point to as constructor parameters,
or it begins empty and the subobjects are added later via access functions or operators.
Because these parts exist outside of the scope of the class, when the class is destroyed, the pointer or reference member variable will be destroyed (but not deleted). Consequently, the parts themselves will still exist.

class Circle
{
private:
     ...
    Point center;
....
};

_______________               _______________
|    Circle   |   -center     |   point     |
|-------------|◆------------->|-------------|
|-------------|              1|-------------|
|_____________|               |_____________|


class X
{
    Y a; // 1; Composition
    Y b[10]; // 0..10; Composition
};

class X
{
    X() { a = new Y[10]; }
    ~X(){ delete [] a; }
    ...
    Y *a; // 0..10; Composition
};

class X {
...
vector a;
};


Summarizing composition and aggregation

Compositions:

Typically use normal member variables
Can use pointer members if the class handles object allocation/deallocation itself
Responsible for creation/destruction of parts
Aggregations:

Typically use pointer or reference members that point to or reference objects that live outside the scope of the aggregate class
Not responsible for creating/destroying parts

////////////////////////////////////////////(5)Inheritance(Generalization)////////////////////////////////////////////
In Inheritance relationship a class is derived from another class. It is a “is a” relationship between two classes.


_______________
|      X      |
|-------------|
|-------------|
|_____________|
      △
      |
      |
      |
_______________
|      Y      |
|-------------|
|-------------|
|_____________|


Here 𝑆ℎ𝑎𝑝𝑒 is an abstract class that is why it is shown in Italics.
𝘋𝘳𝘢𝘸() and 𝘌𝘳𝘦𝘢𝘴𝘦() methods of Shape class is pure virtual function, so it is also shown as italics.


                 ______________
                 |    𝑆ℎ𝑎𝑝𝑒     |
                 |-------------|
                 |-------------|
                 |  +𝘋𝘳𝘢𝘸:𝘷𝘰𝘪𝘥  |
                 |  +𝘌𝘳𝘦𝘢𝘴𝘦:𝘷𝘰𝘪𝘥 |
                 |_____________|
                 ◹            ◸
                /              \
               /                \
              /                  \
_______________                  _______________
|    Circle   |                  |    Ellipse  |
|-------------|                  |-------------|
|-------------|                  |-------------|
|_____________|                  |_____________|



6)Class template

Template class mean generic classes.Languages like C++, java, C# supports generic programming.
Representation

          _______________
          |      Y      |
          |-------------|
__________|-------------|
|      X  |_____________|
|-------------|
|-------------|
|_____________|


*/



int main()
{

}
