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

```
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
```
![PlantUML model](http://www.plantuml.com/plantuml/svg/BSwn3e903CRncJv54nU8CN6-2KON5v-W78rfv7g65WO9x-wTSVr-_-7hpMdnDSrWBz4tBPGmpcGsk2yohiwtcFKX7yOh_007bKGpx71fb187Aw4-4KwDJ0557U7S6FkzOFl76dPXop9Lt6aiEqK_CEMDsovWfIhcv18Fn9XNzIgY3WVqh5Dv-GK0)
[plantuml code](http://www.plantuml.com/plantuml/png/BSwn3e903CRncJv54nU8CN6-2KON5v-W78rfv7g65WO9x-wTSVr-_-7hpMdnDSrWBz4tBPGmpcGsk2yohiwtcFKX7yOh_007bKGpx71fb187Aw4-4KwDJ0557U7S6FkzOFl76dPXop9Lt6aiEqK_CEMDsovWfIhcv18Fn9XNzIgY3WVqh5Dv-GK0)


Different type of members/ methods in a class diagram
1) private members are pointed with ```-```
2) protected members are pointed with ```#``` 
3) public members are pointed with ```+```  
4) S͟t͟a͟t͟i͟c͟ ͟m͟e͟m͟b͟e͟r͟s͟ are represented as underlined.
5) 𝘗𝘶𝘳𝘦 𝘷𝘪𝘳𝘵𝘶𝘢𝘭 functions are represented as italics.


## Class relationship
So far we only have had classes that were consist of primitive types such as int, double and string.
But a class might have relation to other classes, such as inheritance or has a member that is from type of an other class. The following summarize the relationship between classes. 
The following summarize the relationship between classes:

1) Association (knows a, Uses-a) ────────>
2) Dependency (uses a) - - - - - ->
3) Aggregation (has a) ◇────────>
4) Composition (has a) ◆────────>
5) Inheritance (is a) ────────▷
6) Class template

Different Multiplicity in a relation
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

To qualify as a composition, an object and a part must have the following relationship:

1) The part (member) is part of the object (class)
2) The part (member) can only belong to one object (class) at a time
3) The part (member) has its existence managed by the object (class)
4) The part (member) does not know about the existence of the object (class)

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

```
_______________               _______________
|    Circle   |   -center     |   point     |
|─────────────|◆─────────────>|─────────────|
|─────────────|              1|─────────────|
|_____________|               |_____________|
```

```cpp
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
```


### Aggregation
Aggregation can occur when a class is a collection or container of other classes, but where the contained classes
do not have a strong life cycle dependency on the container—essentially, if the container is destroyed,
its contents are not. You may have confusion between aggregation and association.
Association differs from aggregation only in that it does not imply any containment.

To qualify as an aggregation, a whole object and its parts must have the following relationship:

1) The part (member) is part of the object (class)
2) The part (member) can belong to more than one object (class) at a time
3) The part (member) does not have its existence managed by the object (class)
4) The part (member) does not know about the existence of the object (class)

```cpp
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
```

```
_______________               _______________
| Department  | -m_teacher    |   Teacher   |
|─────────────|◇─────────────>|─────────────|
|─────────────|              1|─────────────|
|_____________|               |_____________|

```
A department has a teacher, and the scope of teacher doesn’t depend on the department since a teacher can be
member of another department.

```cpp
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
```




### Association
To qualify as an association, an object and another object must have the following relationship:

1) The associated object (member) is otherwise unrelated to the object (class)
2) The associated object (member) can belong to more than one object (class) at a time
3) The associated object (member) does not have its existence managed by the object (class)
4) The associated object (member) may or may not know about the existence of the object (class)
Because associations are a broad type of relationship, they can be implemented in many different ways.
However, most often, associations are implemented using pointers, where the object points at the associated object.


```cpp
Class X
{
    X(Y *y) : y_ptr(y) {}
    void SetY(Y *y) { y_ptr = y;   }
    void f()        { y_ptr->Foo();}
    ----
    Y *y_ptr; // pointer
};
```

```
_______________        _______________
|       X     |        |     Y       |
|─────────────|───────>|─────────────|
|─────────────|        |─────────────|
|_____________|        |_____________|
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


Refs:   [1](https://cppcodetips.wordpress.com/2013/12/23/uml-class-diagram-explained-with-c-samples/), [2](https://www.learncpp.com/cpp-tutorial/10-1-object-relationships/), [3](https://www.geeksforgeeks.org/unified-modeling-language-uml-sequence-diagrams/)
ASCII codes: [━━━ ─── ► ◄ ▲ ▼ ◆ ◇ ♦ △ ▽ ◁ ▷ ◹ ◸ ◺ ◿](https://www.alt-codes.net/), [𝗕𝗼𝗹𝗱/𝐼𝑡𝑎𝑙𝑖𝑐,u͟n͟d͟e͟r͟l͟i͟n͟e͟](https://yaytext.com/)
