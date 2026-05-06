// Visitor — before/after.
//
// "Before": each new operation (count, call) requires a new method on every
// concrete Color, so adding an operation touches every subclass.
//
// "After": operations live in Visitors. Adding CountVisitor or CallVisitor
// doesn't modify Color/Red/Blu — just create another visitor.

#include <iostream>
#include <memory>
#include <vector>

namespace before_inheritance {

class Color {
public:
    virtual ~Color() = default;
    virtual void count() = 0;
    virtual void call()  = 0;

    static void report() {
        std::cout << "Red=" << redCount_ << " Blu=" << bluCount_ << '\n';
    }

protected:
    static int redCount_;
    static int bluCount_;
};
int Color::redCount_ = 0;
int Color::bluCount_ = 0;

class Red : public Color {
public:
    void count() override { ++redCount_; }
    void call()  override { std::cout << "  Red::showEye\n"; }
};

class Blu : public Color {
public:
    void count() override { ++bluCount_; }
    void call()  override { std::cout << "  Blu::showSky\n"; }
};

}  // namespace before_inheritance

namespace after_visitor {

class Red;
class Blu;

class Visitor {
public:
    virtual ~Visitor() = default;
    virtual void visit(Red& red) = 0;
    virtual void visit(Blu& blu) = 0;
};

class Color {
public:
    virtual ~Color() = default;
    virtual void accept(Visitor& visitor) = 0;
};

class Red : public Color {
public:
    void accept(Visitor& visitor) override { visitor.visit(*this); }
    void showEye() { std::cout << "  Red::showEye\n"; }
};

class Blu : public Color {
public:
    void accept(Visitor& visitor) override { visitor.visit(*this); }
    void showSky() { std::cout << "  Blu::showSky\n"; }
};

class CountVisitor : public Visitor {
public:
    void visit(Red&) override { ++red_; }
    void visit(Blu&) override { ++blu_; }
    void report() const { std::cout << "Red=" << red_ << " Blu=" << blu_ << '\n'; }
private:
    int red_ = 0;
    int blu_ = 0;
};

class CallVisitor : public Visitor {
public:
    void visit(Red& red) override { red.showEye(); }
    void visit(Blu& blu) override { blu.showSky(); }
};

}  // namespace after_visitor

int main() {
    {
        std::cout << "--- before (operations baked into Color) ---\n";
        using namespace before_inheritance;
        std::vector<std::unique_ptr<Color>> set;
        set.push_back(std::make_unique<Red>());
        set.push_back(std::make_unique<Blu>());
        set.push_back(std::make_unique<Blu>());
        set.push_back(std::make_unique<Red>());
        set.push_back(std::make_unique<Red>());
        for (auto& c : set) { c->count(); c->call(); }
        Color::report();
    }

    {
        std::cout << "--- after (operations are visitors) ---\n";
        using namespace after_visitor;
        std::vector<std::unique_ptr<Color>> set;
        set.push_back(std::make_unique<Red>());
        set.push_back(std::make_unique<Blu>());
        set.push_back(std::make_unique<Blu>());
        set.push_back(std::make_unique<Red>());
        set.push_back(std::make_unique<Red>());

        CountVisitor counter;
        CallVisitor caller;
        for (auto& c : set) { c->accept(counter); c->accept(caller); }
        counter.report();
    }
}
