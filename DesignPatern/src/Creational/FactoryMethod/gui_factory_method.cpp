#include <iostream>
#include <memory>
#include <string>

// Abstract Product: Button
class Button {
public:
    virtual void render() = 0;
    virtual ~Button() = default;
};

// Concrete Product: Mac Button
class MacButton : public Button {
public:
    void render() override {
        std::cout << "🍏 Rendering Mac-style button\n";
    }
};

// Concrete Product: Windows Button
class WinButton : public Button {
public:
    void render() override {
        std::cout << "🪟 Rendering Windows-style button\n";
    }
};

// Abstract Factory: ButtonFactory
class ButtonFactory {
public:
    virtual std::unique_ptr<Button> buildButton(const std::string& type) = 0;
    virtual ~ButtonFactory() = default;
};

// Concrete Factory: PlatformFactory
class PlatformFactory : public ButtonFactory {
public:
    std::unique_ptr<Button> buildButton(const std::string& type) override {
        if (type == "Windows") {
            return std::make_unique<WinButton>();
        } else if (type == "Mac") {
            return std::make_unique<MacButton>();
        } else {
            throw std::invalid_argument("Unknown button type: " + type);
        }
    }
};

// Main Function
int main() {
    std::unique_ptr<ButtonFactory> buttonFactory = std::make_unique<PlatformFactory>();

    std::unique_ptr<Button> macButton = buttonFactory->buildButton("Mac");
    macButton->render();

    std::unique_ptr<Button> winButton = buttonFactory->buildButton("Windows");
    winButton->render();

    return 0;
}
