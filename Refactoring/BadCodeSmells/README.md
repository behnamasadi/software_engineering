# Classical Bad Smell

These name have specific meaning and using them help us to talk in an
unambiguous way and avoid miscommunication.

## Bloaters 

Bloaters are codes, and classes that have evolved to such gigantic proportions in which they can hardly function. 
Typically these odors don't pop up immediately, but they accumulate over time as the software progresses
 (and particularly when no one is trying to remove them).

### Long Method
Generally, any method longer than ten lines should be avoided. Since writing code is easier than reading it, the "smell" remains unnoticed until the
 method becomes a hideous, oversized beast.

#### Treatment
In general, if you feel the need to comment about something inside a method, then you should take this code and bring it into a new method.
 Even a single line may and should be split into a separate system, if explanations are needed. And if the method has a clear name, 
no one is going to have to look at the code to see what it does.

### Large Class
A class contains many fields/methods/lines of code.
Extract Class, Extract Subclass to solve the problem.

### Primitive Obsession
If you use some data type like string, int, etc and you pass it to various class,
method and they have to interpert it and do something about it, i.e. you send
tax number/ phone number as sting and every consumer has to interpert the number
/ decipher the number/ decompose it to some city code/ office code etc.
To solve it replace Data Value with Object.


### Long Parameter List
More than three or four parameters for a method should be avoided.


### Data Clumps
when you have two or more piece of data that you always pass them toghther (i.e.
parameters for connecting to a database). These clumps should be turned into
their own classes. If you want to make sure any data is a data clump or not,
simply delete one of the data values and see if the other values are still
valid. If this is not the case, this is a good sign that it is appropriate to
incorporate this group of variables into an entity.


## Object-Orientation Abusers
### Switch Statements replace switch with
polymorphism.

### Temporary Field

### Refused Bequest
If a subclass only uses some of its parents ' inherited methods and resources,
 the hierarchy is off-kilter. The unneeded methods may either go unused or be
redefined to make exceptions usable.

### Alternative Classes with Different Interfaces
Two classes perform identical functions but have different method names.


## Change Preventers
### Divergent Change
### Parallel Inheritance Hierarchies
### Shotgun Surgery


## Dispensables

### Comments
### Duplicate Code
### Data Class
### Dead Code
### Lazy Class
### Speculative Generality

## Couplers  
### Feature Envy

Feature envy is a term used to describe a situation in which one object gets at
the fields of another object in order to perform some sort of computation or
make a decision, rather than asking the object to do the computation itself.

As a trivial example, consider a class representing a rectangle. The user of the
rectangle may need to know its area. The programmer could expose width and
height fields and then do the computation outside of the Rectangle class.
Alternatively, Rectangle could keep the width and height fields private and
provide a getArea method. This is arguably a better approach.

The problem with the first situation, and the reason it is considered a code
smell, is because it breaks encapsulation.

As a rule of thumb, whenever you find yourself making extensive use of fields
from another class to perform any sort of logic or computation, consider moving
that logic to a method on the class itself.

### Inappropriate Intimacy
One class uses the internal fields and methods of another class.


### Message Chains
In code you see a series of calls like: a->b()->c()->d()
It violates the "Law of Demeter" which says:
Only talk to your immediate friends.
violation of this law will cause proliferation of dependencies


### Middle Man
If a class performs only one action, delegating work to another class, why does it exist at all?
A middle man may have been added to avoid interclass dependencies.
Some design patterns create middle man on purpose (such as Proxy or Decorator).


