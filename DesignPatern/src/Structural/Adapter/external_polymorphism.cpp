// Adapter — external polymorphism with a templated wrapper.
//
// `LegacyRectangle` and `LegacyCircle` are unrelated classes that each happen
// to expose a `render()` member. We want to treat them uniformly through a
// common `ExecuteInterface`, without modifying either class or making them
// share a base.
//
// `ExecuteAdapter<T>` is a thin template wrapper that holds a T plus a
// pointer-to-member-function and exposes `execute()`. This is the C++ flavor
// of "external polymorphism": the polymorphism lives in the adapter, not in
// the wrapped types.

#include <iostream>
#include <memory>

class LegacyRectangle {
public:
    void render() const { std::cout << "LegacyRectangle::render\n"; }
};

class LegacyCircle {
public:
    void render() const { std::cout << "LegacyCircle::render\n"; }
};

class ExecuteInterface {
public:
    virtual ~ExecuteInterface() = default;
    virtual void execute() = 0;
};

template <class T>
class ExecuteAdapter : public ExecuteInterface {
public:
    using Method = void (T::*)() const;

    ExecuteAdapter(std::unique_ptr<T> object, Method method)
        : object_(std::move(object)), method_(method) {}

    void execute() override { (object_.get()->*method_)(); }

private:
    std::unique_ptr<T> object_;
    Method method_;
};

int main() {
    std::unique_ptr<ExecuteInterface> shape1 =
        std::make_unique<ExecuteAdapter<LegacyRectangle>>(
            std::make_unique<LegacyRectangle>(), &LegacyRectangle::render);
    std::unique_ptr<ExecuteInterface> shape2 =
        std::make_unique<ExecuteAdapter<LegacyCircle>>(
            std::make_unique<LegacyCircle>(), &LegacyCircle::render);

    shape1->execute();
    shape2->execute();
}
