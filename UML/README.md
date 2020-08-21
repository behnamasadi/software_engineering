# UML Diagrams
1) Structure Diagrams
  - Class Diagram
  - Component Diagram
  - Deployment Diagram
  - Object Diagram
  - Package Diagram
  - Profile Diagram
  - Composite Structure Diagram
2) Behavioral Diagrams
  - Use Case Diagram
  - Activity Diagram
  - State Machine Diagram
  - Sequence Diagram
  - Communication Diagram
  - Interaction Overview Diagram
  - Timing Diagram



## Class Diagram

```cpp
class Animal
{
private:
    std::string name;
protected: 
    int id;
public:
    void setName(std::string name);
    void virtual move();
    static int count();
};
```

Class diagram for the above class is shown below:

![PlantUML model](diagrams/ClassDiagram/Animal.svg)


[plantuml code](diagrams/ClassDiagram/Animal.puml)


Different type of members/ methods in a class diagram
1) private members are pointed with ```-```
2) protected members are pointed with ```#``` 
3) public members are pointed with ```+```  
4) S͟t͟a͟t͟i͟c͟  members are represented as underlined.
5) 𝘗𝘶𝘳𝘦 𝘷𝘪𝘳𝘵𝘶𝘢𝘭 functions are represented as italics.


## Class relationship
So far we only have had classes that were consist of primitive types such as int, double and string.
But a class might have relation to other classes, such as inheritance or has a member that is from type of an other class. The following summarize the relationship between classes. 
The following summarize the relationship between classes:

1) Composition (has a) ◆────────
2) Aggregation (has a) ◇────────
3) Association (knows a, Uses-a) ────────
4) Dependency (uses a) - - - - - ->
5) Inheritance (is a) ────────▷
6) Class template

### Multiplicity in a relation
1) “0..1”               No instances, or one instance (optional, may)
2) “1”                  Exactly one instance
3) “0..* or *”          Zero or more instances
4) “1..*”               One or more instances (at least one)



### Composition
In real-life, complex objects are composed of smaller ones, i.e. a car has engine, some tires, a transmission. 
in C++ when you write a class or struct you are using basic types like int, double or other classes
when constructing a complex object which is object composition.

You can interpret or read object composition relation as ```has a```. A car ```has-a``` frame.
Composition can occur when a class is a collection or container of other classes, but where the 
contained classes have a strong life cycle dependency on the container—essentially, if the container 
is destroyed, its contents are also destroyed.


Composition relationship has the following characteristics:

1) The part is the fraction of the object.
2) The part can only belong to one object at a time.
3) The existence of the part is being managed by the object.
4) The part does not have any information about about the existence of the object.

Compositions are one of the easiest relationship types to implement in C++.
They are typically created as structs or classes with normal data members.
Because these data members exist directly as part of the struct/class, their lifetimes are bound to that
of the class instance itself. Compositions that need to do dynamic allocation or deallocation may be
implemented using pointer data members. In this case, the composition class should be responsible for
doing all necessary memory management itself (not the user of the class).

```cpp
class Point
{
};

class Circle
{
private:
    Point center;
};
```

An other example is heart and person, hear can only belong to one person and if the person dies, the heart will be deleted as well:

```
class Heart
{
};

class Person
{
private:
	Heart heart;
};
```

![PlantUML model](diagrams/ClassDiagram/PersonHeart.svg)


[plantuml code](diagrams/ClassDiagram/PersonHeart.puml)


Folder may contain many files, but each File has exactly one Folder parent. If Folder is deleted, all contained Files are deleted as well.


```cpp

class File
{
    
};
class Folder
{
public:
    vector<File> files;// 0..*; Composition
};
```

![PlantUML model](diagrams/ClassDiagram/FolderFile.svg)


[plantuml code](diagrams/ClassDiagram/FolderFile.puml)


Hospital has 1 or more Departments, and each Department belongs to exactly one Hospital. If Hospital is closed, so are all of its Departments.
```cpp
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
```

![PlantUML model](diagrams/ClassDiagram/HospitalDepartment.svg)


[plantuml code](diagrams/ClassDiagram/HospitalDepartment.puml)


### Aggregation
Aggregation can occur when a class is a collection or container of other classes, but where the contained classes
do not have a strong life cycle dependency on the container—essentially, if the container is destroyed,
its contents are not. You may have confusion between aggregation and association.
Association differs from aggregation only in that it does not imply any containment.

Aggregation relationship has the following characteristics:

1) The part is the fraction of the object.
2) The part can belong to more than one object at a time.
3) The part existence does managed managed by the object.
4) The part does not have any information about about the existence of the object.

```cpp
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
    Proffesor *m_proffesor; 
public:
    Department(Proffesor *proffesor = nullptr): m_proffesor(proffesor){}
};

```
![PlantUML model](diagrams/ClassDiagram/HospitalDepartment.svg)


[plantuml code](diagrams/ClassDiagram/HospitalDepartment.puml)

A Department has a Proffesor, and the scope of Proffesor doesn’t depend on the Department. Many-to-many does not fit very well into an aggregation. Aggregation represents a part-whole relationship. It is verbalized by a "has a" verb. Thus, modeling a many-to-many relationship as an aggregation introduces a faulty design and should be expressed via association.

```cpp

Proffesor *proffesor = new Proffesor("Bob");
{
	Department dept(proffesor);
}
std::cout << proffesor->getName() << " still exists!";
delete proffesor;

```
and other implementation would be via reference variable: 
```cpp
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
    Proffesor  m_proffesor;
public:
    Department(const Proffesor& proffesor ): m_proffesor(proffesor){}
};
```

Since the Department might have several Proffesor, if we use a vector (which makes a copy of the sent object) we will get an if we send 
a reference object (reference object can not be copied). The solution is `std::reference_wrapper`. It is a class that allows assignment and copying,
but behave like a reference

```cpp
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

    Proffesor Bob("Bob");
    Proffesor Jim("Jim");
    {
        Department dept;
        dept.addProffesor(Bob);
        dept.addProffesor(Jim);
    }
    std::cout << Bob.getName() << " still exists!";
    std::cout << Jim.getName() << " still exists!";


```

![PlantUML model](diagrams/ClassDiagram/StudentTeacher.svg)


[plantuml code](diagrams/ClassDiagram/StudentTeacher.puml)

### Association

In an association, there is no implication of whole/part relationship (just like we had in aggregation and composition). A good example of such relationship is the relationship between teachers and students (doctors and patients). The teacher (doctor) has a relationship with the student (patients), but the teacher (doctor) is not a part/whole student (patients). A teacher (doctor) can see many student (patients), and a student (patients) can see many teacher (doctor) and neither teacher (doctor) nor student (patients) manage each other lifespans.

Association relationship has the following characteristics:

1) The associated objects is unrelated to the object.
2) The associated object can belong to more than one object at a time.
3) The associated object existence does  managed by the object.
4) The associated object may or may not know about the existence of the object.
Because associations are a broad type of relationship, they can be implemented in many different ways.
However, most often, associations are implemented using pointers, where the object points at the associated object.


```cpp
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

```




### Dependency
One class depends on another if the independent class is a parameter variable or local variable of a method of the dependent class

```cpp
class X {
 ...
 void f1(Y y)  {…;  y.Foo();       }
 void f2(Y *y) {…;  y->Foo();      }
 void f3(Y &y) {…;  y.Foo();       }
 void f4()     {   Y y; y.Foo();  …}
 void f5()     {…; Y::StaticFoo(); }
};
```

```
_______________            _______________
|       X     |            |     Y       |
|─────────────|- - - - - ->|─────────────|
|─────────────|            |─────────────|
|_____________|            |_____________|
```






#### Composition vs Aggregation
Composition is the stronger form of aggregation. Because aggregations are similar to compositions in that they are both part-whole relationships,
they are implemented almost identically, and the difference between them is mostly semantic.
In a composition, we typically add our parts to the composition using normal member variables
(or pointers where the allocation and deallocation process is handled by the composition class).
In an aggregation, we also add parts as member variables. However, these member variables are typically either
references or pointers that are used to point at objects that have been created outside the scope of the class.
Consequently, an aggregation usually either takes the objects it is going to point to as constructor parameters,
or it begins empty and the subobjects are added later via access functions or operators.
Because these parts exist outside of the scope of the class, when the class is destroyed, the pointer or reference member variable will be destroyed (but not deleted). Consequently, the parts themselves will still exist.



#### Summarizing composition and aggregation

**Compositions**:

1) Typically use normal member variables.
2) Can use pointer members if the class handles object allocation/deallocation itself.
3) Responsible for creation/destruction of parts.


**Aggregations**:

1) Typically use pointer or reference members that point to or reference objects that live outside the scope of the aggregate class
2) Not responsible for creating/destroying parts

### Inheritance(Generalization)
In Inheritance relationship a class is derived from another class. It is a “is a” relationship between two classes.

```
_______________
|      X      |
|─────────────|
|─────────────|
|_____________|
      △
      |
      |
      |
_______________
|      Y      |
|─────────────|
|─────────────|
|_____________|
```

Here 𝑆ℎ𝑎𝑝𝑒 is an abstract class that is why it is shown in Italics.
𝘋𝘳𝘢𝘸() and 𝘌𝘳𝘦𝘢𝘴𝘦() methods of Shape class is pure virtual function, so it is also shown as italics.

```
                 ______________
                 |    𝑆ℎ𝑎𝑝𝑒     |
                 |─────────────|
                 |─────────────|
                 |+𝘋𝘳𝘢𝘸:𝘷𝘰𝘪𝘥   |
                 |+𝘌𝘳𝘦𝘢𝘴𝘦:𝘷𝘰𝘪𝘥  |
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

```

### Class template

Template class mean generic classes.Languages like C++, java, C# supports generic programming.
Representation

```
          _______________
          |      Y      |
          |-------------|
__________|-------------|
|      X  |_____________|
|-------------|
|-------------|
|_____________|
```
## Sequence Diagram
UML sequence diagram shows how objects in a system  or classes in the code interact with each other, in the order they take place and they show a sequence of events. The main purpose is to document processes and understand the requirement of a program.

1) **Actors** are always outside the scope of the system in a sequence diagram. 
2) **Objects** are represented by rectangles. Object that participate in the interaction are at the top of the diagram and you put the object that initiate the interaction in the left and place increasingly more subordinate objects to the right.
3) **Life line** is a vertical dash line that shows the existance of object over a period of time.
4) **Messeges** show the information being sent between objects (solid line). When and object a message back, this is called a return or reply message (dash line).
  -  **Synchronous messages**: A synchronous message waits for a reply before the interaction can move forward. The sender waits until the receiver has completed the processing of the message. The caller continues only when it knows that the receiver has processed the previous message i.e. it receives a reply message.
  -  **Asynchronous Messages**: An asynchronous message does not wait for a reply from the receiver. The interaction moves forward irrespective of the receiver processing the previous message or not. We use a lined arrow head to represent an asynchronous message.

```
       ┌─┐                                      
       ║"│                                      
       └┬┘                                      
       ┌┼┐                                      
        │            ┌───────┐          ┌──────┐
       ┌┴┐           │Theater│          │Server│
      user           └───┬───┘          └──┬───┘
       │   Insert card   │                 │    
       │ ───────────────>│                 │    
       │                 │                 │    
       │   Select date   │                 │    
       │ ───────────────>│                 │    
       │                 │                 │    
       │   Offer seat    │                 │    
       │ <─ ─ ─ ─ ─ ─ ─ ─│                 │    
       │                 │                 │    
       │  Submit order   │                 │    
       │ ───────────────>│                 │    
       │                 │                 │    
       │                 │  Submit order   │    
       │                 │────────────────>│    
       │                 │                 │    
       │                 │Order Confirmed  │    
       │                 │<────────────────│    
       │                 │                 │    
       │ Order Confirmed │                 │    
       │ <───────────────│                 │    
      user           ┌───┴───┐          ┌──┴───┐
       ┌─┐           │Theater│          │Server│
       ║"│           └───────┘          └──────┘
       └┬┘                                      
       ┌┼┐                                      
        │                                       
       ┌┴┐     
```

![PlantUML model](http://www.plantuml.com/plantuml/svg/PP114e8m34NtESM_01TWmJ3ZoXKBl41jmzWPA4n8FRyHqQ8ky_xxJIVjgauqJoCvhxCWhooq68e-BYufBZTs-iDwbhkXfrirRwF6EHbGU2VXB-jvPAy8Dj4EKPbWdgNTCDYy6jwAA4tKVRvEKJ5BO2dLPlz4ZMCEUb4SLtTRSfhJ46NYy7cZRFyMGA2MKx2ZF000)

#### Class relationship in nutshell
Association is a pointer to an other class and life cycle doesn't depend on the class.  
Aggregation is vague concept and could be similar to Association.  
Dependency is done via sending an object via function parameter.  
Composition is when a class has member of an other class and maintains the life cycle.  
## Use Case Diagram


## Activity Diagram


Refs:   [1](https://cppcodetips.wordpress.com/2013/12/23/uml-class-diagram-explained-with-c-samples/), 
	[2](https://www.learncpp.com/cpp-tutorial/10-1-object-relationships/), 
	[3](https://www.geeksforgeeks.org/unified-modeling-language-uml-sequence-diagrams/),
	[4](https://www.uml-diagrams.org/)
ASCII codes: [━━━ ─── ► ◄ ▲ ▼ ◆ ◇ ♦ △ ▽ ◁ ▷ ◹ ◸ ◺ ◿](https://www.alt-codes.net/), [𝗕𝗼𝗹𝗱/𝐼𝑡𝑎𝑙𝑖𝑐,u͟n͟d͟e͟r͟l͟i͟n͟e͟](https://yaytext.com/)
