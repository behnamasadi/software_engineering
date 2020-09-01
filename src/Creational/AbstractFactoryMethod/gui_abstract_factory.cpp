#include <iostream>
#define LINUX

using namespace std;

namespace before
{

class Widget
{
public:
    virtual void draw() = 0;
};

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

class Widget
{
public:
    virtual void draw() = 0;
};

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


class Factory
{
public:
    virtual Widget *create_button() = 0;
    virtual Widget *create_menu() = 0;
};

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
