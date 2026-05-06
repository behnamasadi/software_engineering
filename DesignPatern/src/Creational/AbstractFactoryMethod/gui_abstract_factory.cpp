// Abstract Factory — before/after.
//
// "Before": every code path that creates a widget hard-codes per-platform
// ifdef branches. Adding a new platform means hunting through every site.
//
// "After": a WidgetFactory hides the platform decision. The Client just
// asks for buttons and menus and never knows which OS it's on.

#include <iostream>
#include <memory>

namespace before_ifdef_everywhere {

class Widget {
public:
    virtual ~Widget() = default;
    virtual void render() = 0;
};

class LinuxButton : public Widget {
public:
    void render() override { std::cout << "[linux]   button\n"; }
};
class LinuxMenu : public Widget {
public:
    void render() override { std::cout << "[linux]   menu\n"; }
};
class WindowsButton : public Widget {
public:
    void render() override { std::cout << "[windows] button\n"; }
};
class WindowsMenu : public Widget {
public:
    void render() override { std::cout << "[windows] menu\n"; }
};

class Client {
public:
    void render() {
#ifdef WINDOWS_BUILD
        auto w = std::make_unique<WindowsButton>();
#else
        auto w = std::make_unique<LinuxButton>();
#endif
        w->render();
    }
    // Every other window/dialog repeats the same #ifdef.
};

}  // namespace before_ifdef_everywhere

namespace after_abstract_factory {

class Widget {
public:
    virtual ~Widget() = default;
    virtual void render() = 0;
};

class LinuxButton : public Widget {
public:
    void render() override { std::cout << "[linux]   button\n"; }
};
class LinuxMenu : public Widget {
public:
    void render() override { std::cout << "[linux]   menu\n"; }
};
class WindowsButton : public Widget {
public:
    void render() override { std::cout << "[windows] button\n"; }
};
class WindowsMenu : public Widget {
public:
    void render() override { std::cout << "[windows] menu\n"; }
};

class WidgetFactory {
public:
    virtual ~WidgetFactory() = default;
    virtual std::unique_ptr<Widget> createButton() = 0;
    virtual std::unique_ptr<Widget> createMenu()   = 0;
};

class LinuxFactory : public WidgetFactory {
public:
    std::unique_ptr<Widget> createButton() override { return std::make_unique<LinuxButton>(); }
    std::unique_ptr<Widget> createMenu()   override { return std::make_unique<LinuxMenu>(); }
};

class WindowsFactory : public WidgetFactory {
public:
    std::unique_ptr<Widget> createButton() override { return std::make_unique<WindowsButton>(); }
    std::unique_ptr<Widget> createMenu()   override { return std::make_unique<WindowsMenu>(); }
};

class Client {
public:
    explicit Client(std::unique_ptr<WidgetFactory> f) : factory_(std::move(f)) {}

    void renderWindow() {
        auto button = factory_->createButton();
        auto menu   = factory_->createMenu();
        button->render();
        menu->render();
    }

private:
    std::unique_ptr<WidgetFactory> factory_;
};

}  // namespace after_abstract_factory

int main() {
    std::cout << "--- before (ifdef everywhere) ---\n";
    {
        before_ifdef_everywhere::Client c;
        c.render();
    }

    std::cout << "--- after (abstract factory) ---\n";
    {
        // Client never sees a Linux/Windows type — only WidgetFactory.
        std::unique_ptr<after_abstract_factory::WidgetFactory> factory =
            std::make_unique<after_abstract_factory::LinuxFactory>();
        after_abstract_factory::Client client(std::move(factory));
        client.renderWindow();
    }
}
