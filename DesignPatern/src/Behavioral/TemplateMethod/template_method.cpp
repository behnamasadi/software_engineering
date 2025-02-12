#include <iostream>
#include <memory>
#include <vector>

class Base
{
protected:
    void stepA()
    {
        std::cout << "Step A -> ";
    }
    void stepC()
    {
        std::cout << "Step C -> ";
    }
    void stepE()
    {
        std::cout << "Step E";
    }

    // Abstract methods (placeholders)
    virtual void stepB() = 0;
    virtual void stepD() = 0;

public:
    virtual ~Base() = default;

    void run()
    {
        stepA();
        stepB();
        stepC();
        stepD();
        stepE();
        std::cout << '\n';
    }
};

class DerivedOne : public Base
{
protected:
    void stepB() override
    {
        std::cout << "Step B1 -> ";
    }
    void stepD() override
    {
        std::cout << "Step D1 -> ";
    }
};

class DerivedTwo : public Base
{
protected:
    void stepB() override
    {
        std::cout << "Step B2 -> ";
    }
    void stepD() override
    {
        std::cout << "Step D2 -> ";
    }
};

int main()
{
    std::vector<std::unique_ptr<Base>> objects;
    objects.push_back(std::make_unique<DerivedOne>());
    objects.push_back(std::make_unique<DerivedTwo>());

    for (const auto& obj : objects)
    {
        obj->run();
    }

    return 0;
}
