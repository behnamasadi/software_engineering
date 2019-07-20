#include <iostream>
#define LINUX

using namespace std;

namespace before
{
/**
 * Abstract base product.
 */
class Widget
{
public:
    virtual void draw() = 0;
};

/**
 * Concrete product family 1.
 */
class LinuxButton : public Widget
{
public:
    void draw() { cout << "LinuxButton\n"; }
};

class LinuxMenu : public Widget
{
public:
    void draw() { cout << "LinuxMenu\n"; }
};

/**
 * Concrete product family 2.
 */
class WindowsButton : public Widget
{
public:
    void draw() { cout << "WindowsButton\n"; }
};

class WindowsMenu : public Widget
{
public:
    void draw() { cout << "WindowsMenu\n"; }
};

/**
 * Here's a client, which uses concrete products directly.
 * It's code filled up with nasty switch statements
 * which check the product type before its use.
 */
class Client
{
public:
    void draw()
    {
        #ifdef LINUX
        Widget *w = new LinuxButton;
        #else // WINDOWS
        Widget *w = new WindowsButton;
        #endif
        w->draw();
        display_window_one();
        display_window_two();
    }

    void display_window_one()
    {
        #ifdef LINUX
        Widget *w[] =
        {
            new LinuxButton,
            new LinuxMenu
        };
        #else // WINDOWS
        Widget *w[] =
        {
            new WindowsButton,
            new WindowsMenu
        };
        #endif
        w[0]->draw();
        w[1]->draw();
    }

    void display_window_two()
    {
        #ifdef LINUX
        Widget *w[] =
        {
            new LinuxMenu,
            new LinuxButton
        };
        #else // WINDOWS
        Widget *w[] =
        {
            new WindowsMenu,
            new WindowsButton
        };
        #endif
        w[0]->draw();
        w[1]->draw();
    }
};
}


namespace after
{
/**
* Abstract base product. It should define an interface
* which will be common to all products. Clients will
* work with products through this interface, so it
* should be sufficient to use all products.
*/
class Widget
{
public:
    virtual void draw() = 0;
};

/**
* Concrete product family 1.
*/
class LinuxButton : public Widget
{
public:
    void draw() { cout << "LinuxButton\n"; }
};

class LinuxMenu : public Widget
{
public:
    void draw() { cout << "LinuxMenu\n"; }
};

/**
* Concrete product family 2.
*/
class WindowsButton : public Widget
{
public:
    void draw() { cout << "WindowsButton\n"; }
};

class WindowsMenu : public Widget
{
public:
    void draw() { cout << "WindowsMenu\n"; }
};

/**
* Abstract factory defines methods to create all
* related products.
*/
class Factory
{
public:
    virtual Widget *create_button() = 0;
    virtual Widget *create_menu() = 0;
};

/**
* Each concrete factory corresponds to one product
* family. It creates all possible products of
* one kind.
*/
class LinuxFactory : public Factory
{
public:
    Widget *create_button()
    {
        return new LinuxButton;
    }

    Widget *create_menu()
    {
        return new LinuxMenu;
    }
};

/**
* Concrete factory creates concrete products, but
* returns them as abstract.
*/
class WindowsFactory : public Factory
{
    public:
    Widget *create_button()
    {
        return new WindowsButton;
    }

    Widget *create_menu()
    {
        return new WindowsMenu;
    }
};

/**
* Client receives a factory object from its creator.
*
* All clients work with factories through abstract
* interface. They don't know concrete classes of
* factories. Because of this, you can interchange
* concrete factories without breaking clients.
*
* Clients don't know the concrete classes of created
* products either, since abstract factory methods
* returns abstract products.
*/
class Client
{
private:
    Factory *factory;

public:
    Client(Factory *f)
    {
        factory = f;
    }

    void draw()
    {
        Widget *w = factory->create_button();
        w->draw();
        display_window_one();
        display_window_two();
    }

    void display_window_one()
    {
        Widget *w[] = {factory->create_button(),factory->create_menu()};
        w[0]->draw();
        w[1]->draw();
    }

void display_window_two()
    {
        Widget *w[] = {factory->create_menu(), factory->create_button() };
        w[0]->draw();
        w[1]->draw();
    }
};


}

int main()
{
    {
        before::Client *c = new before::Client();
        c->draw();
    }


    /**
    * Now the nasty switch statement is needed only once to
    * pick and create a proper factory. Usually that's
    * happening somewhere in program initialization code.
    */


    {
        after::Factory *factory;
        #ifdef LINUX
            factory = new after::LinuxFactory;
        #else // WINDOWS
            factory = new after::WindowsFactory;
        #endif

        after::Client *c = new after::Client(factory);
        c->draw();
    }




}
