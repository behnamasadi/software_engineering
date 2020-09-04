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
Two major varieties. The two main variations of the Factory Method pattern are
(1) the case when the Creator class is an abstract class and does not provide an
implementation for the factory method it declares, and (2) the case when the
Creator is a concrete class and provides a default implementation for the factory
method. It's also possible to have an abstract class that defines a default
implementation, but this is less common.
The first case requires subclasses to define an implementation, because there's
no reasonable default. It gets around the dilemma of having to instantiate
unforeseeable classes. In the second case, the concrete Creator uses the factory
method primarily for flexibility. It's following a rule that says, "Create objects in
a separate operation so that subclasses can override the way they're created."
This rule ensures that designers of subclasses can change the class of objects
their parent class instantiates if necessary.
2. Parameterized factory methods. Another variation on the pattern lets the factory
method create multiple kinds of products. The factory method takes a parameter
that identifies the kind of object to create. All objects the factory method creates
will share the Product interface. In the Document example, Application might
support different kinds of Documents. You pass CreateDocument an extra
parameter to specify the kind of document to create.

magine programming a video game, where you would like to add new types of enemies in the future, each of which has different AI functions and can update differently. By using a factory method, the controller of the program can call to the factory to create the enemies, without any dependency or knowledge of the actual types of enemies. Now, future developers can create new enemies, with new AI controls and new drawing member functions, add it to the factory, and create a level which calls the factory, asking for the enemies by name. Combine this method with an XML description of levels, and developers could create new levels without having to recompile their program. All this, thanks to the separation of creation of objects from the usage of objects.



Discussion. Frameworks are applications (or subsystems) with "holes" in them. Each framework specifies the infrastructure, superstructure, and flow of control for its "domain", and the client of the framework may: exercise the framework's default behavior "as is", extend selected pieces of the framework, or replace selected pieces.

The Factory Method pattern addresses the notion of "creation" in the context of frameworks. In this example, the framework knows WHEN a new document should be created, not WHAT kind of Document to create. The "placeholder" Application::CreateDocument() has been declared by the framework, and the client is expected to "fill in the blank" for his/her specific document(s). Then, when the client asks for Application::NewDocument(), the framework will subsequently call the client's MyApplication::CreateDocument().


## Singleton
Private constructor
static member
static function


Refs:
	[1](https://www.youtube.com/watch?v=KBkkEKNlE6I),
	[2](https://www.youtube.com/watch?v=D1CnNAszv_M&list=PLk6CEY9XxSIDZhQURp6d8Sgp-A0yKKDKV&index=6)

