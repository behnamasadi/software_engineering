//https://www.bogotobogo.com/DesignPatterns/factorymethod.php
#include <iostream>
#include <cstring>
class Button {
public:
	virtual void paint() = 0;
};
 
class OSXButton: public Button {
public:
	void paint() {
		std::cout << "OSX button \n";
	}
};
 
class WindowsButton: public Button  {
public:
	void paint() {
		std::cout << "Windows button \n";
	}
};
 
class GUIFactory {
public:
	virtual Button *createButton(char *) = 0;
};

class Factory: public GUIFactory {
public:
	Button *createButton(char *type) {
		if(strcmp(type,"Windows") == 0) {
			return new WindowsButton;
		}
		else if(strcmp(type,"OSX") == 0) {
			return new OSXButton;
		}
	}
};

int main()
{
	GUIFactory* guiFactory;
	Button *btn;

	guiFactory = new Factory;

	btn = guiFactory->createButton("OSX");
	btn -> paint();
	btn = guiFactory->createButton("Windows");
	btn -> paint();

	return 0;
}
