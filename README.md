# [UML, Design Pattern and Refactoring](#)
This repository contains an introduction on **UML** with C++ examples, various example of **Design Pattern** in object oriented programming with C++, **code refactoring**, and few examples for software design such **Model View Controller (MVC)**, **SOLID Design Principles** and finally examples of **Clean Code**.

## [UML](#) 
- [Concepts](UML/Concepts) 
- [Structure Diagrams](UML/StructureDiagrams/)
   * [Class Diagram](UML/StructureDiagrams/ClassDiagram)
   * [Component Diagram](UML/StructureDiagrams/ComponentDiagram)
   * [Deployment Diagram](UML/StructureDiagrams/DeploymentDiagram)
   * [Object Diagram](UML/StructureDiagrams/ObjectDiagram)
   * [Package Diagram](UML/StructureDiagrams/PackageDiagram)
   * [Profile Diagram](UML/StructureDiagrams/ProfileDiagram)
   * [Composite Structure Diagram](UML/StructureDiagrams/CompositeStructureDiagram)
- [Behavioral Diagrams](UML/BehavioralDiagrams)
   * [Use Case Diagram](UML/BehavioralDiagrams/UseCaseDiagram)
   * [Activity Diagram](UML/BehavioralDiagrams/ActivityDiagram)
   * [State Machine Diagram](UML/BehavioralDiagrams/StateMachineDiagram)
   * [Sequence Diagram](UML/BehavioralDiagrams/SequenceDiagram)
   * [Communication Diagram](UML/BehavioralDiagrams/CommunicationDiagram)
   * [Interaction Overview Diagram](UML/BehavioralDiagrams/InteractionOverviewDiagram)
   * [Timing Diagram](UML/BehavioralDiagrams/TimingDiagram)
- [Extensibility](UML/Extensibility)


ASCII codes and UML diagrams:
	[1](http://www.plantuml.com/plantuml/umla/),
	[2](https://www.alt-codes.net/), 
	[3](https://yaytext.com/)

References:   
	[1](https://cppcodetips.wordpress.com/2013/12/23/uml-class-diagram-explained-with-c-samples/), 
	[2](https://www.learncpp.com/cpp-tutorial/10-1-object-relationships/), 
	[3](https://www.wikiwand.com/en/Class_diagram),
	[4](https://www.uml-diagrams.org/),
	[5](https://www.visual-paradigm.com/guide/uml-unified-modeling-language/uml-class-diagram-tutorial/),
	[6](https://www.ibm.com/support/knowledgecenter/SS8PJ7_9.7.0/com.ibm.xtools.modeler.doc/topics/cdepend.html)
	[7](http://www.cs.sjsu.edu/~pearce/modules/lectures/oop/basics/interfaces.htm)
	[8](https://martinfowler.com/bliki/BallAndSocket.html)

    
|   |   |   |
|---|---|---|
|<a target="_blank"  href="https://www.amazon.com/gp/product/0596009828/ref=as_li_tl?ie=UTF8&camp=1789&creative=9325&creativeASIN=0596009828&linkCode=as2&tag=rosdev09-20&linkId=2690ec967b66a97892f0dc164b3451cb"><img border="0" src="images/Learning_UML_2.0__A_Pragmatic_Introduction_to_UML.jpg" ></a><img src="//ir-na.amazon-adsystem.com/e/ir?t=rosdev09-20&l=am2&o=1&a=0596009828" width="1" height="1" border="0" alt="" style="border:none !important; margin:0px !important;" />|<a target="_blank"  href="https://www.amazon.com/gp/product/0321321278/ref=as_li_tl?ie=UTF8&camp=1789&creative=9325&creativeASIN=0321321278&linkCode=as2&tag=rosdev09-20&linkId=daa19c0aab2d0a02aa6877635026ccc3"><img border="0" src="images/UML_2_and_the_Unified_Process__Practical_Object-Oriented_Analysis_and_Design_(2nd_Edition).jpg" ></a><img src="//ir-na.amazon-adsystem.com/e/ir?t=rosdev09-20&l=am2&o=1&a=0321321278" width="1" height="1" border="0" alt="" style="border:none !important; margin:0px !important;" />|<a target="_blank"  href="https://www.amazon.com/gp/product/0321193687/ref=as_li_tl?ie=UTF8&camp=1789&creative=9325&creativeASIN=0321193687&linkCode=as2&tag=rosdev09-20&linkId=657a0bf853a4191b25a2d6a8d8c44d95"><img border="0" src="images/UML_Distilled__A_Brief_Guide_to_the_Standard_Object_Modeling_Language.jpg" ></a><img src="//ir-na.amazon-adsystem.com/e/ir?t=rosdev09-20&l=am2&o=1&a=0321193687" width="1" height="1" border="0" alt="" style="border:none !important; margin:0px !important;" />


## [SOLID Design Principles](SOLID)  
- [Single responsibility principle](SOLID/SingleResponsibilityPrinciple)  
- [Open–closed principle](SOLID/OpenClosedPrinciple)  
- [Liskov substitution principle](SOLID/LiskovSubstitutionPrinciple)  
- [Interface segregation principle](SOLID/InterfaceSegregationPrinciple)  
- [Dependency inversion principle](SOLID/DependencyInjection)  


## [Model View Controller](ModelViewController)  
- [Simple Model View Controller Example](ModelViewController/src/student_model_view_controller.cpp)

## [Rule Of Three/Five/Zero](RuleOfThreeFiveZero)
- [Rule Of Five](RuleOfThreeFiveZero/src/rule_of_five.cpp)  
- [Rule Of Three](RuleOfThreeFiveZero/src/rule_of_three.cpp)  
- [Rule Of Zero](RuleOfThreeFiveZero/src/rule_of_zero.cpp)  

## [DesignPatern](#) 
- [Behavioral patterns](DesignPatern/src/Behavioral)
  * [Chain of responsibility](DesignPatern/src/Behavioral/README.md#chain-of-responsibility)  
  * [Command](DesignPatern/src/Behavioral/README.md#command)  
  * [Interpreter](DesignPatern/src/Behavioral/README.md##interpreter)  
  * [Iterator](DesignPatern/src/Behavioral/README.md#iterator)  
  * [Mediator](DesignPatern/src/Behavioral/README.md#mediator)  
  * [Memento](DesignPatern/src/Behavioral/README.md#memento)  
  * [Null Object](DesignPatern/src/Behavioral/README.md#nullobject)  
  * [Observer](DesignPatern/src/Behavioral/README.md#observer)  
  * [State](DesignPatern/src/Behavioral/README.md#state)  
  * [Strategy](DesignPatern/src/Behavioral/README.md#strategy)  
  * [Template method](DesignPatern/src/Behavioral/README.md#template-method)  
  * [Visitor](DesignPatern/src/Behavioral/README.md#visitor)  
- [Creational patterns](DesignPatern/src/Creational/)
  * [Abstract Factory](DesignPatern/src/Creational/README.md#abstractfactory)  
  * [Builder](DesignPatern/src/Creational/README.md#builder)  
  * [Factory Method](DesignPatern/src/Creational/README.md#factory-method)  
  * [Object Pool](DesignPatern/src/Creational/README.md#Objectpool)  
  * [Prototype](DesignPatern/src/Creational/README.md#prototype)  
  * [Singleton](DesignPatern/src/Creational/README.md#singleton)  
- [Structural patterns](DesignPatern/src/Structural)
  * [Adapter](DesignPatern/src/Structural/README.md#adapter)  
  * [Bridge](DesignPatern/src/Structural/README.md#bridge)  
  * [Composite](DesignPatern/src/Structural/README.md#composite)  
  * [Decorator](DesignPatern/src/Structural/README.md#decorator)  
  * [Facade](DesignPatern/src/Structural/README.md#facade)  
  * [Flyweight](DesignPatern/src/Structural/README.md#flyweight)  
  * [Private Class Data](DesignPatern/src/Structural/README.md#private-class-data)  
  * [Proxy](DesignPatern/src/Structural/README.md#proxy)  


References:
	[1](https://en.wikibooks.org/wiki/C%2B%2B_Programming/Code/Design_Patterns), 
	[2](https://sourcemaking.com/design_patterns/),
	[3](https://refactoring.guru/), 
	[4](https://cpppatterns.com/), 
	[5](https://www.youtube.com/playlist?list=PLrhzvIcii6GNjpARdnO4ueTUAVR9eMBpc),
	[6](https://www.bogotobogo.com/DesignPatterns/),
	[7](https://www.growingwiththeweb.com/p/explore.html?t=Design%20pattern),
	[8](https://www.tutorialspoint.com/design_pattern/),
	[9](http://simpletechtalks.com/tag/design-patterns/),
	[10](http://www.vishalchovatiya.com/iterator-design-pattern-in-modern-cpp/),
	[11](https://cppcodetips.wordpress.com/category/design-pattern/),
	[12](https://caiorss.github.io/C-Cpp-Notes/cpp-design-patterns.html),
	[13](https://readthedocs.org/projects/cpp-design-patterns/downloads/pdf/latest/)

|   |   |   |
|---|---|---|
|<a target="_blank"  href="https://www.amazon.com/gp/product/0201633612/ref=as_li_tl?ie=UTF8&camp=1789&creative=9325&creativeASIN=0201633612&linkCode=as2&tag=rosdev09-20&linkId=175fc3c33d5c7f359af5401c1250f192"><img border="0" src="images/Design_Patterns._Elements_of_Reusable_Object-Oriented_Software.jpg" ></a><img src="//ir-na.amazon-adsystem.com/e/ir?t=rosdev09-20&l=am2&o=1&a=0201633612" width="1" height="1" border="0" alt="" style="border:none !important; margin:0px !important;" />|<a target="_blank"  href="https://www.amazon.com/gp/product/0596007124/ref=as_li_tl?ie=UTF8&camp=1789&creative=9325&creativeASIN=0596007124&linkCode=as2&tag=rosdev09-20&linkId=76b4256e75432f557909a43e0a9de1a2"><img border="0" src="images/Head_First_Design_Patterns_(A_Brain_Friendly_Guide).jpg" ></a><img src="//ir-na.amazon-adsystem.com/e/ir?t=rosdev09-20&l=am2&o=1&a=0596007124" width="1" height="1" border="0" alt="" style="border:none !important; margin:0px !important;" />|<a target="_blank"  href="https://www.amazon.com/gp/product/1484236025/ref=as_li_tl?ie=UTF8&camp=1789&creative=9325&creativeASIN=1484236025&linkCode=as2&tag=rosdev09-20&linkId=974576fff321c67154d6bc7299956ef0"><img border="0" src="images/Design_Patterns_in_Modern_C++__Reusable_Approaches_for_Object-Oriented_Software_Design.jpg" ></a><img src="//ir-na.amazon-adsystem.com/e/ir?t=rosdev09-20&l=am2&o=1&a=1484236025" width="1" height="1" border="0" alt="" style="border:none !important; margin:0px !important;" />|

## [Refactoring](#) 
- [Bad Code Smells](Refactoring/BadCodeSmells)
  * [Bloaters](Refactoring/BadCodeSmells/Bloaters)
  * [ChangePreventers](Refactoring/BadCodeSmells/ChangePreventers)
  * [Couplers](Refactoring/BadCodeSmells/Couplers)
  * [Dispensables](Refactoring/BadCodeSmells/Dispensables)
  * [Object-Orientation Abusers](Refactoring/BadCodeSmells/Object-OrientationAbusers)
- [Refactoring Techniques](#)
  * [Composing Methods](Refactoring/RefactoringTechniques/ComposingMethods)
  * [Dealing With Generalisation](Refactoring/RefactoringTechniques/DealingWithGeneralisation)
  * [Moving Features Between Objects](Refactoring/RefactoringTechniques/MovingFeaturesBetweenObjects)
  * [Organizing Data](Refactoring/RefactoringTechniques/OrganizingData)
  * [Simplifying Conditional Expressions](Refactoring/RefactoringTechniques/SimplifyingConditionalExpressions)
  * [Simplifying Method Calls](Refactoring/RefactoringTechniques/SimplifyingMethodCalls)

References:
	[1](https://refactoring.guru/refactoring),
	[2](https://sourcemaking.com/refactoring),
	[3](https://www.refactoring.com/)

|   |   |   |
|---|---|---|
|<a target="_blank"  href="https://www.amazon.com/gp/product/0132350882/ref=as_li_tl?ie=UTF8&camp=1789&creative=9325&creativeASIN=0132350882&linkCode=as2&tag=rosdev09-20&linkId=949bad73dc39e53caf1caf849ad0f565"><img border="0" src="images/Refactoring_Improving_the_Design_of_Existing_Code_Martin_Fowler.jpg" ></a><img src="//ir-na.amazon-adsystem.com/e/ir?t=rosdev09-20&l=am2&o=1&a=0132350882" width="1" height="1" border="0" alt="" style="border:none !important; margin:0px !important;" />|<a target="_blank"  href="https://www.amazon.com/gp/product/B07XGR7QQD/ref=as_li_tl?ie=UTF8&camp=1789&creative=9325&creativeASIN=B07XGR7QQD&linkCode=as2&tag=rosdev09-20&linkId=44172741182e66512df744aa85f17756"><img border="0" src="images/Clean_Code_A_Handbook_of_Agile_Software_Craftsmanship_Robert_C._Martin.jpg" ></a><img src="//ir-na.amazon-adsystem.com/e/ir?t=rosdev09-20&l=am2&o=1&a=B07XGR7QQD" width="1" height="1" border="0" alt="" style="border:none !important; margin:0px !important;" />|   |


<small><i>TOC generated with <a href='http://ecotrust-canada.github.io/markdown-toc/'>markdown-toc</a></i></small>


[![Build Status](https://travis-ci.com/behnamasadi/software_engineering.svg?branch=master)](https://travis-ci.com/behnamasadi/software_engineering)
![alt text](https://img.shields.io/badge/license-BSD-blue.svg)


