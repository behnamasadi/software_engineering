// Abstract Factory — minimal skeleton.
//
// AbstractProduct: IButton
// ConcreteProducts: WinButton, OSXButton
// AbstractFactory: IGUIFactory
// ConcreteFactories: WinFactory, OSXFactory

#include <iostream>
#include <memory>

class IButton {
public:
    virtual ~IButton() = default;
    virtual void paint() = 0;
};

class WinButton : public IButton {
public:
    void paint() override { std::cout << "Win button painted\n"; }
};

class OSXButton : public IButton {
public:
    void paint() override { std::cout << "OSX button painted\n"; }
};

class IGUIFactory {
public:
    virtual ~IGUIFactory() = default;
    virtual std::unique_ptr<IButton> createButton() = 0;
};

class WinFactory : public IGUIFactory {
public:
    std::unique_ptr<IButton> createButton() override {
        return std::make_unique<WinButton>();
    }
};

class OSXFactory : public IGUIFactory {
public:
    std::unique_ptr<IButton> createButton() override {
        return std::make_unique<OSXButton>();
    }
};

enum class Appearance { Win, Mac };

std::unique_ptr<IGUIFactory> makeFactory(Appearance a) {
    switch (a) {
        case Appearance::Win: return std::make_unique<WinFactory>();
        case Appearance::Mac: return std::make_unique<OSXFactory>();
    }
    return nullptr;  // unreachable
}

int main() {
    auto factory = makeFactory(Appearance::Mac);
    auto button  = factory->createButton();
    button->paint();
}
