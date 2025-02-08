#include <functional>
#include <iostream>
#include <memory>

namespace before {

class robot {
public:
  virtual void search() = 0;
  virtual void attack() = 0;
  virtual void defend() = 0;
  virtual ~robot() = default;
};

class linear : public robot {
public:
  void search() override { std::cout << "linear search" << std::endl; }
};

class linearPinch : public linear {
public:
  void attack() override { std::cout << "pinch attack" << std::endl; }
};

class linearPinchRun : public linearPinch {
public:
  void defend() override { std::cout << "run defense" << std::endl; }
};

class linearPunch : public linear {
public:
  void attack() override { std::cout << "punch attack" << std::endl; }
};

class linearPunchRun : public linearPunch {
public:
  void defend() override { std::cout << "run defense" << std::endl; }
};

class spiral : public robot {
public:
  void search() override { std::cout << "spiral search" << std::endl; }
};

class spiralPinch : public spiral {
public:
  void attack() override { std::cout << "pinch attack" << std::endl; }
};

class spiralPinchRun : public spiralPinch {
public:
  void defend() override { std::cout << "run defense" << std::endl; }
};

} // namespace before

// Runtime polymorphism
namespace after {

class robot;

class Search {
public:
  virtual void apply(robot *r) const = 0;
  virtual ~Search() = default;
};

class Attack {
public:
  virtual void apply(robot *r) const = 0;
  virtual ~Attack() = default;
};

class Defend {
public:
  virtual void apply(robot *r) const = 0;
  virtual ~Defend() = default;
};

class robot {
  std::unique_ptr<Search> m_search;
  std::unique_ptr<Attack> m_attack;
  std::unique_ptr<Defend> m_defend;

public:
  robot(std::unique_ptr<Search> search, std::unique_ptr<Attack> attack,
        std::unique_ptr<Defend> defend)
      : m_search(std::move(search)), m_attack(std::move(attack)),
        m_defend(std::move(defend)) {}

  void attack() { m_attack->apply(this); }

  void defend() { m_defend->apply(this); }

  void search() { m_search->apply(this); }
};

class linear : public Search {
public:
  void apply(robot *r) const override {
    std::cout << "search(linear)" << std::endl;
  }
};

class spiral : public Search {
public:
  void apply(robot *r) const override {
    std::cout << "search(spiral)" << std::endl;
  }
};

class punch : public Attack {
public:
  void apply(robot *r) const override {
    std::cout << "punch(attack)" << std::endl;
  }
};

class pinch : public Attack {
public:
  void apply(robot *r) const override {
    std::cout << "pinch(attack)" << std::endl;
  }
};

class run : public Defend {
public:
  void apply(robot *r) const override {
    std::cout << "run(defend)" << std::endl;
  }
};

} // namespace after

// Compile-time polymorphism
namespace functionPtr {

class robot {
public:
  using Search = std::function<void(robot *)>;
  using Attack = std::function<void(robot *)>;
  using Defend = std::function<void(robot *)>;

  Search m_search;
  Attack m_attack;
  Defend m_defend;

  robot(Search search, Attack attack, Defend defend)
      : m_search(search), m_attack(attack), m_defend(defend) {}

  void attack() { m_attack(this); }

  void defend() { m_defend(this); }

  void search() { m_search(this); }
};

class Search {
public:
  void operator()(robot *r) { std::cout << "Search (strategy)" << std::endl; }
};

class Attack {
public:
  void operator()(robot *r) { std::cout << "punch(attack)" << std::endl; }
};

class Defend {
public:
  void operator()(robot *r) { std::cout << "run(defend)" << std::endl; }
};

} // namespace functionPtr

template <typename T> void go(T *r) {
  r->search();
  r->attack();
  r->defend();
}

int main() {
  {
    std::unique_ptr<before::robot> r1 =
        std::make_unique<before::linearPinchRun>();
    go(r1.get());
    std::unique_ptr<before::robot> r2 =
        std::make_unique<before::linearPunchRun>();
    go(r2.get());
    std::unique_ptr<before::robot> r3 =
        std::make_unique<before::spiralPinchRun>();
    go(r3.get());
  }

  {
    std::unique_ptr<after::robot> r1 = std::make_unique<after::robot>(
        std::make_unique<after::linear>(), std::make_unique<after::punch>(),
        std::make_unique<after::run>());
    std::unique_ptr<after::robot> r2 = std::make_unique<after::robot>(
        std::make_unique<after::linear>(), std::make_unique<after::pinch>(),
        std::make_unique<after::run>());
    std::unique_ptr<after::robot> r3 = std::make_unique<after::robot>(
        std::make_unique<after::spiral>(), std::make_unique<after::pinch>(),
        std::make_unique<after::run>());

    go(r1.get());
    go(r2.get());
    go(r3.get());
  }

  {
    functionPtr::Attack punch;
    functionPtr::Search linearsearch;
    functionPtr::Defend defend;
    functionPtr::robot r1(linearsearch, punch, defend);
    go(&r1);

    functionPtr::robot r2(linearsearch, punch, [](functionPtr::robot *r) {
      std::cout << "hide(defend)" << std::endl;
    });
    go(&r2);
  }
}
