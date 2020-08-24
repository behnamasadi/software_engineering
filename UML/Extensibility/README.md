## Extensibility
They allow designers to extend the vocabulary of UML in order to create new model elements

### Stereotype
Stereotype is rendered as a name enclosed by guillemets `« »` or `<< >>` and placed above the name of another element. A stereotyped model type can
 appear in a project many times. For example, when modeling an online shopping system with use case diagram you might have multiple actors 
who are <<administrator>>. Same for class model, you might have multiple <<Enum>> or <<Model>> classes. 
A stereotype uses the same notation as a class, with the keyword `«stereotype»` shown before or above the name of the stereotype. S
A stereotype cannot be used by itself, but must always be used with one of the metaclasses it extends.
Stereotype can change the graphical appearance of the extended model element by using attached icons represented by the Image profile class.

![PlantUML model](diagrams/WebClientUser.svg.svg)

[plantuml code](diagrams/WebClientUser.svg.puml)

### Tag



### Constraints



Refs:
	[1](https://www.uml-diagrams.org/stereotype.html),
	[2](https://www.uml-diagrams.org/profile-metaclass.html),
	[3](https://www.visual-paradigm.com/support/documents/vpuserguide/1283/27/6258_taggedvalues.html),
	[4](https://www.visual-paradigm.com/guide/uml-unified-modeling-language/how-to-model-constraints-in-uml/)
