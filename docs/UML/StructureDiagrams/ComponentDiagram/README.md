## Component Diagram


Component is a **set of classes with a well-defined interface**. They can be used to represent an architecture.
Components are connected through implemented and required interfaces, often using the `ball-andsocket notation` just as for class diagrams. You can also decompose components by using `composite structure` diagrams. A component is similar to a black box whose external behavior is defined by a provided interface and required interfaces.



![PlantUML model](diagrams/ComponentUML2.0Notation.svg)

[plantuml code](diagrams/ComponentUML2.0Notation.puml)



In this example, a POS machine can connect to a sales server component, using a sales message interface. 
Because the network is unreliable, a message queue component is set up so the POS machine can talk to the server
 when the network is up and talk to a queue when the network is down. 
The queue will then talk to the server when the network becomes available. As a result, the message queue both supplies the 
sales message interface to talk with the POS machine and requires that interface to talk with the server. The server is broken down into two
major components. The transaction processor realizes the sales message interface, and the accounting driver talks to the accounting system.

![PlantUML model](diagrams/SalesServer.svg)

[plantuml code](diagrams/SalesServer.puml)

Components are not a technology. Technology people seem to find this hard to
understand. Components are about how customers want to relate to software. They
want to be able to buy their software a piece at a time, and to be able to upgrade it
just like they can upgrade their stereo. They want new pieces to work seamlessly with
their old pieces, and to be able to upgrade on their own schedule, not the
manufacturer's schedule. They want to be able to mix and match pieces from various
manufacturers. This is a very reasonable requirement. It is just hard to satisfy. **Ralph Johnson**


Ref:
	[1](https://www.geeksforgeeks.org/unified-modeling-language-uml-object-diagrams/),
	[2](https://www.guru99.com/component-diagram-uml-example.html),
	[3](https://www.guru99.com/component-diagram-uml-example.html),
	[4](https://www.smartdraw.com/component-diagram/),
	[5](http://www.c2.com/cgi/wiki?DoComponentsExist),
	[6](https://www.lucidchart.com/pages/uml-component-diagram)

	
