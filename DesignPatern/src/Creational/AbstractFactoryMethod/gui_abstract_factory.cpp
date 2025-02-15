#include <iostream>
#include <memory>

#define LINUX

using namespace std;

namespace before
{
class Widget
{
public:
    virtual void render() = 0;
    virtual ~Widget() = default;
};

class LinuxButton : public Widget
{
public:
    void render() override { cout << "🟢 Linux Button Rendered\n"; }
};

class LinuxMenu : public Widget
{
public:
    void render() override { cout << "🟢 Linux Menu Rendered\n"; }
};

class WindowsButton : public Widget
{
public:
    void render() override { cout << "🟦 Windows Button Rendered\n"; }
};

class WindowsMenu : public Widget
{
public:
    void render() override { cout << "🟦 Windows Menu Rendered\n"; }
};

class Client
{
public:
    void render()
    {
#ifdef LINUX
        unique_ptr<Widget> w = make_unique<LinuxButton>();
#else
        unique_ptr<Widget> w = make_unique<WindowsButton>();
#endif
        w->render();
        displayWindowOne();
        displayWindowTwo();
    }

    void displayWindowOne()
    {
#ifdef LINUX
        unique_ptr<Widget> w1 = make_unique<LinuxButton>();
        unique_ptr<Widget> w2 = make_unique<LinuxMenu>();
#else
        unique_ptr<Widget> w1 = make_unique<WindowsButton>();
        unique_ptr<Widget> w2 = make_unique<WindowsMenu>();
#endif
        w1->render();
        w2->render();
    }

    void displayWindowTwo()
    {
#ifdef LINUX
        unique_ptr<Widget> w1 = make_unique<LinuxMenu>();
        unique_ptr<Widget> w2 = make_unique<LinuxButton>();
#else
        unique_ptr<Widget> w1 = make_unique<WindowsMenu>();
        unique_ptr<Widget> w2 = make_unique<WindowsButton>();
#endif
        w1->render();
        w2->render();
    }
};
}

namespace after
{
class Widget
{
public:
    virtual void render() = 0;
    virtual ~Widget() = default;
};

class LinuxButton : public Widget
{
public:
    void render() override { cout << "🟢 Linux Button Rendered\n"; }
};

class LinuxMenu : public Widget
{
public:
    void render() override { cout << "🟢 Linux Menu Rendered\n"; }
};

class WindowsButton : public Widget
{
public:
    void render() override { cout << "🟦 Windows Button Rendered\n"; }
};

class WindowsMenu : public Widget
{
public:
    void render() override { cout << "🟦 Windows Menu Rendered\n"; }
};

// Abstract Factory Interface
class WidgetFactory
{
public:
    virtual unique_ptr<Widget> createButton() = 0;
    virtual unique_ptr<Widget> createMenu() = 0;
    virtual ~WidgetFactory() = default;
};

// Concrete Factory for Linux UI
class LinuxFactory : public WidgetFactory
{
public:
    unique_ptr<Widget> createButton() override
    {
        return make_unique<LinuxButton>();
    }

    unique_ptr<Widget> createMenu() override
    {
        return make_unique<LinuxMenu>();
    }
};

// Concrete Factory for Windows UI
class WindowsFactory : public WidgetFactory
{
public:
    unique_ptr<Widget> createButton() override
    {
        return make_unique<WindowsButton>();
    }

    unique_ptr<Widget> createMenu() override
    {
        return make_unique<WindowsMenu>();
    }
};

class Client
{
private:
    unique_ptr<WidgetFactory> factory;

public:
    explicit Client(unique_ptr<WidgetFactory> f) : factory(move(f)) {}

    void render()
    {
        unique_ptr<Widget> w = factory->createButton();
        w->render();
        displayWindowOne();
        displayWindowTwo();
    }

    void displayWindowOne()
    {
        unique_ptr<Widget> w1 = factory->createButton();
        unique_ptr<Widget> w2 = factory->createMenu();
        w1->render();
        w2->render();
    }

    void displayWindowTwo()
    {
        unique_ptr<Widget> w1 = factory->createMenu();
        unique_ptr<Widget> w2 = factory->createButton();
        w1->render();
        w2->render();
    }
};
}

int main()
{
    cout << "\n🌍 BEFORE: Hardcoded UI Elements\n";
    {
        before::Client c;
        c.render();
    }

    cout << "\n🌍 AFTER: Using Abstract Factory\n";
    {
        unique_ptr<after::WidgetFactory> factory;

#ifdef LINUX
        factory = make_unique<after::LinuxFactory>();
#else
        factory = make_unique<after::WindowsFactory>();
#endif

        unique_ptr<after::Client> c = make_unique<after::Client>(move(factory));
        c->render();
    }

    return 0;
}
