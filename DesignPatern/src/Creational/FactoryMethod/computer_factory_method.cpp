// Factory Method — pick a Computer subtype by string key.
// The factory hides the concrete classes from the caller.

#include <iostream>
#include <memory>
#include <string>

class Computer {
public:
    virtual ~Computer() = default;
    virtual void start() = 0;
    virtual void shutdown() = 0;
};

class Laptop : public Computer {
public:
    void start()    override { std::cout << "  laptop: running\n"; }
    void shutdown() override { std::cout << "  laptop: hibernating\n"; }
};

class Desktop : public Computer {
public:
    void start()    override { std::cout << "  desktop: powered on\n"; }
    void shutdown() override { std::cout << "  desktop: shut down\n"; }
};

class ComputerFactory {
public:
    static std::unique_ptr<Computer> create(const std::string& type) {
        if (type == "laptop")  return std::make_unique<Laptop>();
        if (type == "desktop") return std::make_unique<Desktop>();
        return nullptr;
    }
};

int main() {
    auto laptop = ComputerFactory::create("laptop");
    auto desktop = ComputerFactory::create("desktop");

    if (laptop)  { laptop->start();  laptop->shutdown(); }
    if (desktop) { desktop->start(); desktop->shutdown(); }
}
