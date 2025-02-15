#include <iostream>
#include <string>
#include <vector>
#include <memory>

class Shape
{
protected:
    std::string m_name;

public:
    explicit Shape(std::string name = "") : m_name(std::move(name)) {}

    virtual void draw() const = 0;

    virtual ~Shape() = default;  // Ensure proper polymorphic destruction
};

class Circle : public Shape
{
public:
    explicit Circle(std::string name) : Shape(std::move(name)) {}

    void draw() const override
    {
        std::cout << "Drawing Circle: " << m_name << std::endl;
    }
};

class Rectangle : public Shape
{
public:
    explicit Rectangle(std::string name) : Shape(std::move(name)) {}

    void draw() const override
    {
        std::cout << "Drawing Rectangle: " << m_name << std::endl;
    }
};

class Group : public Shape
{
private:
    std::vector<std::unique_ptr<Shape>> m_objects;

public:
    explicit Group(std::string name) : Shape(std::move(name)) {}

    void draw() const override
    {
        std::cout << "Drawing Group: " << m_name << std::endl;
        for (const auto& obj : m_objects)
        {
            obj->draw();
        }
    }

    void add(std::unique_ptr<Shape> object)
    {
        m_objects.push_back(std::move(object));
    }
};

int main()
{
    auto root = std::make_unique<Group>("Root");

    auto circle1 = std::make_unique<Circle>("Circle1");
    auto circle2 = std::make_unique<Circle>("Circle2");
    auto rectangle1 = std::make_unique<Rectangle>("Rectangle1");

    auto subgroup = std::make_unique<Group>("Subgroup1");
    subgroup->add(std::make_unique<Circle>("Circle3"));
    subgroup->add(std::make_unique<Rectangle>("Rectangle2"));

    root->add(std::move(circle1));
    root->add(std::move(circle2));
    root->add(std::move(rectangle1));
    root->add(std::move(subgroup));

    root->draw();  // Displays the full hierarchy

    return 0;
}
