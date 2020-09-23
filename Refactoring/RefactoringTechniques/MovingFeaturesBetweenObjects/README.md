# Moving Features between Objects

These refactoring techniques show how to safely move functionality between classes, create new classes, and hide implementation details 
from public access.

## Move Method
A method is used more in another class than in its own class.

Before:
```cpp
class Point{};

class Logger
{
public:
    void Log(std::string msg){}
};

class Shape
{
private:
    Point pivot;
public:
void LogDrawing(Logger logger)
{
    std::string msg = "Shape is drawn at {pivot.X}, {pivot.Y}";
    logger.Log(msg);
}
};
```
After:

```cpp

class Point{};
class Shape
{
private:
    Point pivot;
public:

};
class Logger
{
public:
    void Log(std::string msg){}
    void LogDrawing(Shape shape)
    {
        std::string msg = "Shape is drawn at {pivot.X}, {pivot.Y}";
        this->Log(msg);
    }
};
```

## Move Field
A field is used more in another class than in its own class. Create a field in a new class and redirect all users of the old field to it.

Before:
```cpp
class DiscountRate{};

class Plan{};

class Customer
{
    Plan m_plan;
    DiscountRate m_discountRate;
public:
    Plan plan() {return this->m_plan;}
    DiscountRate discountRate() {return this->m_discountRate;}
};
```
After:
```cpp
class DiscountRate{};

class Plan
{
public:
    DiscountRate m_discountRate;
};

class Customer
{
    Plan m_plan;

public:
    Plan plan() {return this->m_plan;}
    DiscountRate discountRate() {return this->m_plan.m_discountRate;}
};
```



## Extract Class
When one class does the work of two, awkwardness results. Instead, create a new class and place the fields and methods responsible for the relevant functionality in it.

Before:
```cpp
class Person
{
private:
    std::string name;
    std::string officeAreaCode;
    std::string officeNumber;
public:
    std::string getTelephoneNumber()
    {
        return officeAreaCode+officeNumber;
    }
};
```


After:
```cpp
class TelephoneNumber
{
    std::string officeAreaCode;
    std::string officeNumber;
public:
    std::string getTelephoneNumber()
    {
        return officeAreaCode+officeNumber;
    }
    
};

class Person
{
private:
    std::string name;
    TelephoneNumber telephoneNumber;
public:
    std::string getTelephoneNumber()
    {
        return telephoneNumber.getTelephoneNumber();
    }
};
```


## Inline Class
A class does almost nothing and isn’t responsible for anything, and no additional responsibilities are planned for it. Move all features from the class to another one.

Before:
```cpp
class Color {};

class Painter
{
private:
    Color m_Color;
    void InitPainter(Color color)
    {
      //init painter
    }

public:
    Painter(Color c)
    {
        m_Color = c;
        InitPainter(m_Color);
    }
};

class Circle
{
private:
    Painter* m_Painter;
public:
    Circle(Color c)
    {
        m_Painter = new Painter(c);
    }
};
```


After:
```cpp
class Color{};

class Circle
{
private:
    Color m_Color;
    void InitPainter(Color color)
    {
     //init painter
    }

public:
    Circle(Color c)
    {
        m_Color = c;
        InitPainter(m_Color);
    }
};

```

## Hide Delegate
The client (main) gets object B (department) from a field or method of object А (person). Then the client calls a method of object B (department.getManager()).

Create a new method in class A that delegates the call to object B (person.getManager()). Now the client doesn’t know about,
 or depend on, class B.

Before:
```cpp
class Manager{};

class Department
{
    Manager m_manager;
public:
    Manager getManager()
    {
        return m_manager;
    }
};

class Person
{
    Department department;
public:
    Department getdepartment()
    {
        return department;
    }
};

int main()
{
    Person person;
    Department department= person.getdepartment();
    Manager manager= department.getManager();
}
```


After:
```cpp
class Manager{};

class Department
{
    Manager m_manager;
public:
    Manager getManager()
    {
        return m_manager;
    }
};

class Person
{
    Department department;
public:
    Department getdepartment()
    {
        return department;
    }
    Manager getManager()
    {
        return department.getManager();
    }
};

int main()
{
    Person person;
    Manager manager= person.getManager();
}
```
## Remove Middle Man

A class has too many methods that simply delegate to other objects. Delete these methods and force the client to call the end methods directly.
It is inverse of `Hide Delegate`.


## Introduce Foreign Method

A utility class (Date) doesn’t contain the method that you need and you can’t add the method to the class.
Add the method to a client class (Report) and pass an object of the utility class to it as an argument.

Before:
```cpp

class Report 
{
    void sendReport() 
    {
        Date *nextDay = new Date(previousEnd.getYear(), previousEnd.getMonth(), previousEnd.getDate() + 1);

    }
}
```

After:

```cpp
class Report
{
    void sendReport()
    {
        Date newStart = nextDay(previousEnd);
    }

    Date nextDay(Date arg)
    {
        return new Date(arg.getYear(), arg.getMonth(), arg.getDate() + 1);
    }
}
```

## Introduce Local Extension

A utility class doesn’t contain some methods that you need. But you can’t add these methods to the class.
Create a new class containing the methods and make it either the child or wrapper of the utility class.
Sometimes utility class blocks inheritance (by using `final`). Wrapper is the alternate solution.


Before:
```cpp
```


After:
```cpp
```
