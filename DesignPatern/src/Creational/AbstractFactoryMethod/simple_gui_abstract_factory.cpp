#include <iostream>
#include <string>

class IButton
{
public:
    void virtual  Paint(){}
};

class IGUIFactory
{
public:
    virtual IButton *  CreateButton(){}
};

class WinButton :public  IButton
{
    public:
    void Paint()
    {
        //Render a button in a Windows style
    }
};

class WinFactory : public IGUIFactory
{
public:
    IButton * CreateButton()
    {
        return new WinButton();
    }
};

class OSXButton : public IButton
{
    public:
    void Paint()
    {
        //Render a button in a Mac OS X style
    }
};

class OSXFactory : public IGUIFactory
{
public:
    IButton * CreateButton()
    {
        return new OSXButton();
    }
};

enum class APPEARANCE
{
     WIN, MAC
};

/*
Abstract factory ==> IGUIFactory
WinFactory ==> concrete factory1
OSXFactory ==> concrete factory2

Abstract ProductA ==> IButton
ProductA1 ==> OSXButton
ProductA2 ==> WinButton
*/


int main()
{
    APPEARANCE appearance = APPEARANCE::MAC;

    IGUIFactory *factory;
    switch (appearance)
    {
        case APPEARANCE::WIN:
            factory = new WinFactory();
            break;
        case APPEARANCE::MAC:
            factory = new OSXFactory();
            break;
    }

    IButton* button = factory->CreateButton();
    //auto button = factory->CreateButton();
    button->Paint();
}

