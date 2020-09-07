## AbstractFactory
Supporting new kinds of products is difficult. Extending abstract factories to
produce new kinds of Products isn't easy. That's because the AbstractFactory
interface fixes the set of products that can be created. Supporting new kinds of
products requires extending the factory interface, which involves changing the
AbstractFactory class and all of its subclasses. We discuss one solution to this
problem in the Implementation section.

AbstractFactory classes are often implemented with factory methods (Factory Method
(107)), but they can also be implemented using Prototype (117).
95A concrete factory is often a singleton (Singleton (127)).


**Abstract Factory** has the factory object producing objects of several classes. 
**Builder** has the factory object building a complex product incrementally using a correspondingly complex protocol. 
**Prototype** has the factory object (aka prototype) building a product by copying a prototype object.
Abstract Factory can be used as an alternative to **Facade** to hide platform-specific classes.
Abstract Factory classes are often implemented with **Factory Methods**, but they can also be implemented using Prototype.

Abstract Factory classes are often implemented with Factory Methods, but they can also be implemented using Prototype.
Abstract Factory can be used as an alternative to Facade to hide platform-specific classes.


## Builder
The Builder Creational Pattern is used to separate the construction of a complex object from its representation so that the same construction process can create different objects representations.


Abstract Factory (87) is similar to Builder in that it too may construct complex objects.
The primary difference is that the Builder pattern focuses on constructing a complex
object step by step. Abstract Factory's emphasis is on families of product objects (either
simple or complex). Builder returns the product as a final step, but as far as the Abstract
Factory pattern is concerned, the product gets returned immediately.

creat complex object and there is a dependency between them and you want to creat it step by step
step by step is the requiremenet and there is a depenedncy between those objects



## Factory Method

Imagine programming a video game, where you would like to add new types of enemies in the future, each of which has different AI functions 
and can update differently. By using a factory method, the controller of the program can call to the factory to create the enemies, 
without any dependency or knowledge of the actual types of enemies.
 Now, future developers can create new enemies, with new AI controls and new drawing member functions, add it to the factory, and create a 
level which calls the factory, asking for the enemies by name. Combine this method with an XML description of levels, and developers could
 create new levels without having to recompile their program. All this, thanks to the separation of creation of objects from the usage of objects.

![PlantUML model](diagrams/abstract_factory.svg)

[plantuml code](diagrams/abstract_factory.puml)


Factory Method Defines an interface for creating an object, but let subclasses decide which class to instantiate. 
Factory Method is being iften used as the standard way to create objects.


## Singleton
Private constructor
static member
static function


Refs:
	[1](https://www.youtube.com/watch?v=KBkkEKNlE6I),
	[2](https://www.youtube.com/watch?v=D1CnNAszv_M&list=PLk6CEY9XxSIDZhQURp6d8Sgp-A0yKKDKV&index=6)

