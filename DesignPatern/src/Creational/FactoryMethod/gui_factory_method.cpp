// Factory Method — produce per-platform Buttons through a single API.

#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>

class Button {
public:
    virtual ~Button() = default;
    virtual void render() = 0;
};

class MacButton : public Button {
public:
    void render() override { std::cout << "  Mac button\n"; }
};

class WinButton : public Button {
public:
    void render() override { std::cout << "  Windows button\n"; }
};

class ButtonFactory {
public:
    virtual ~ButtonFactory() = default;
    virtual std::unique_ptr<Button> create(const std::string& type) = 0;
};

class PlatformButtonFactory : public ButtonFactory {
public:
    std::unique_ptr<Button> create(const std::string& type) override {
        if (type == "Mac")     return std::make_unique<MacButton>();
        if (type == "Windows") return std::make_unique<WinButton>();
        throw std::invalid_argument("Unknown button type: " + type);
    }
};

int main() {
    std::unique_ptr<ButtonFactory> factory = std::make_unique<PlatformButtonFactory>();

    factory->create("Mac")->render();
    factory->create("Windows")->render();
}
