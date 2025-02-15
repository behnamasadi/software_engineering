#include <iostream>
#include <memory>
#include <string>

// Abstract Product: Computer
class Computer
{
public:
    virtual void start() = 0;
    virtual void shutdown() = 0;
    virtual ~Computer() = default;
};

// Concrete Product: Laptop
class Laptop : public Computer
{
private:
    bool isHibernating = true;

public:
    void start() override 
    { 
        isHibernating = false; 
        std::cout << "💻 Laptop is running.\n"; 
    }

    void shutdown() override 
    { 
        isHibernating = true; 
        std::cout << "💤 Laptop is hibernating.\n"; 
    }

    ~Laptop() override 
    { 
        std::cout << "💻 Laptop destroyed.\n"; 
    }
};

// Concrete Product: Desktop
class Desktop : public Computer
{
private:
    bool isRunning = false;

public:
    void start() override 
    { 
        isRunning = true; 
        std::cout << "🖥️ Desktop is powered on.\n"; 
    }

    void shutdown() override 
    { 
        isRunning = false; 
        std::cout << "🔌 Desktop is shut down.\n"; 
    }

    ~Desktop() override 
    { 
        std::cout << "🖥️ Desktop destroyed.\n"; 
    }
};

// Factory Class
class ComputerFactory
{
public:
    static std::unique_ptr<Computer> createComputer(const std::string& type)
    {
        if (type == "laptop")
            return std::make_unique<Laptop>();
        if (type == "desktop")
            return std::make_unique<Desktop>();
        return nullptr;
    }
};

// Main Function
int main()
{
    std::unique_ptr<Computer> myLaptop = ComputerFactory::createComputer("laptop");
    std::unique_ptr<Computer> myDesktop = ComputerFactory::createComputer("desktop");

    if (myLaptop)
    {
        myLaptop->start();
        myLaptop->shutdown();
    }

    if (myDesktop)
    {
        myDesktop->start();
        myDesktop->shutdown();
    }

    return 0;
}
