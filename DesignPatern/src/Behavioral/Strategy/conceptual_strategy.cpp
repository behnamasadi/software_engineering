#include <iostream>
#include <memory>

class Strategy {
public:
  virtual void solve() = 0;
  virtual ~Strategy() = default; // Virtual destructor to ensure proper cleanup
};

class ConcreteStrategy1 : public Strategy {
public:
  void solve() override {
    std::cout << "ConcreteStrategy1 solution" << std::endl;
  }
};

class ConcreteStrategy2 : public Strategy {
public:
  void solve() override {
    std::cout << "ConcreteStrategy2 solution" << std::endl;
  }
};

class Context {
  std::shared_ptr<Strategy>
      m_strategy; // Use shared_ptr to avoid dangling pointer issues

public:
  explicit Context(std::shared_ptr<Strategy> strategy = nullptr)
      : m_strategy(std::move(strategy)) {}

  void setStrategy(std::shared_ptr<Strategy> strategy) {
    m_strategy = std::move(strategy);
  }

  void execute() {
    if (m_strategy) {
      m_strategy->solve();
    } else {
      std::cerr << "Error: No strategy set!" << std::endl;
    }
  }
};

int main() {
  auto strategy1 = std::make_shared<ConcreteStrategy1>();
  auto strategy2 = std::make_shared<ConcreteStrategy2>();

  Context context(strategy1);
  context.execute();

  context.setStrategy(strategy2);
  context.execute();

  return 0;
}
