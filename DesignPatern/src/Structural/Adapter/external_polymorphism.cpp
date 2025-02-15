#include <iostream>
#include <memory>

class LegacyRectangle
{
public:
    void render()
    {
        std::cout << "Legacy Rectangle render()" << std::endl;
    }
};

class LegacyCircle
{
public:
    void render()
    {
        std::cout << "Legacy Circle render()" << std::endl;
    }
};

class ExecuteInterface
{
public:
    virtual ~ExecuteInterface() = default;
    virtual void execute() = 0;
};

template <class ClassType>
class ExecuteAdapter : public ExecuteInterface
{
    std::unique_ptr<ClassType> m_object;
    void (ClassType::*m_method)();

public:
    ExecuteAdapter(std::unique_ptr<ClassType> object, void (ClassType::*method)())
        : m_object(std::move(object)), m_method(method) {}

    void execute() override
    {
        (m_object.get()->*m_method)();
    }
};

int main()
{
    std::unique_ptr<ExecuteInterface> shape1 = std::make_unique<ExecuteAdapter<LegacyRectangle>>(
        std::make_unique<LegacyRectangle>(), &LegacyRectangle::render);
    shape1->execute();

    std::unique_ptr<ExecuteInterface> shape2 = std::make_unique<ExecuteAdapter<LegacyCircle>>(
        std::make_unique<LegacyCircle>(), &LegacyCircle::render);
    shape2->execute();
}
