// Composite — treat individual objects and groups uniformly through one
// interface. A `Group` is itself a `Shape`, so a group can contain shapes or
// other groups. The client calls `draw()` once on the root and the call
// recurses through the tree.

#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

class Shape {
public:
    explicit Shape(std::string name) : name_(std::move(name)) {}
    virtual ~Shape() = default;
    virtual void draw() const = 0;

protected:
    std::string name_;
};

class Circle : public Shape {
public:
    using Shape::Shape;
    void draw() const override {
        std::cout << "Circle: " << name_ << '\n';
    }
};

class Rectangle : public Shape {
public:
    using Shape::Shape;
    void draw() const override {
        std::cout << "Rectangle: " << name_ << '\n';
    }
};

// Composite: holds children and forwards `draw()` to each one.
class Group : public Shape {
public:
    using Shape::Shape;

    void add(std::unique_ptr<Shape> child) {
        children_.push_back(std::move(child));
    }

    void draw() const override {
        std::cout << "Group: " << name_ << '\n';
        for (const auto& child : children_) child->draw();
    }

private:
    std::vector<std::unique_ptr<Shape>> children_;
};

int main() {
    auto root = std::make_unique<Group>("Root");
    root->add(std::make_unique<Circle>("Circle1"));
    root->add(std::make_unique<Circle>("Circle2"));
    root->add(std::make_unique<Rectangle>("Rectangle1"));

    auto sub = std::make_unique<Group>("Subgroup1");
    sub->add(std::make_unique<Circle>("Circle3"));
    sub->add(std::make_unique<Rectangle>("Rectangle2"));
    root->add(std::move(sub));

    root->draw();
}
