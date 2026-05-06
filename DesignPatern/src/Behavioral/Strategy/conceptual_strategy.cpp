// Strategy — conceptual skeleton.
// Context delegates the variable part of the algorithm to a Strategy object
// that the client can swap in.

#include <iostream>
#include <memory>
#include <utility>

class Strategy {
public:
    virtual ~Strategy() = default;
    virtual void solve() = 0;
};

class StrategyA : public Strategy {
public:
    void solve() override { std::cout << "A solves\n"; }
};

class StrategyB : public Strategy {
public:
    void solve() override { std::cout << "B solves\n"; }
};

class Context {
public:
    explicit Context(std::unique_ptr<Strategy> s = nullptr) : strategy_(std::move(s)) {}

    void setStrategy(std::unique_ptr<Strategy> s) { strategy_ = std::move(s); }

    void run() {
        if (!strategy_) { std::cerr << "no strategy\n"; return; }
        strategy_->solve();
    }

private:
    std::unique_ptr<Strategy> strategy_;
};

int main() {
    Context context(std::make_unique<StrategyA>());
    context.run();

    context.setStrategy(std::make_unique<StrategyB>());
    context.run();
}
