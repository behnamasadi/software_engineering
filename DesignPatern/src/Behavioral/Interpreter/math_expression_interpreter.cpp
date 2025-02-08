#include <iostream>
#include <memory>

// Expression Interface
class Expression {
public:
  virtual int interpret() const = 0;
  virtual ~Expression() = default;
};

// Number Expression (Terminal Expression)
class Number : public Expression {
  int value;

public:
  explicit Number(int val) : value(val) {}
  int interpret() const override { return value; }
};

// Addition Expression (Non-Terminal Expression)
class Addition : public Expression {
  std::shared_ptr<Expression> left;
  std::shared_ptr<Expression> right;

public:
  Addition(std::shared_ptr<Expression> l, std::shared_ptr<Expression> r)
      : left(std::move(l)), right(std::move(r)) {}

  int interpret() const override {
    return left->interpret() + right->interpret();
  }
};

int main() {
  // Represents expression: (5 + 10)
  std::shared_ptr<Expression> expr = std::make_shared<Addition>(
      std::make_shared<Number>(5), std::make_shared<Number>(10));

  std::cout << "Result: " << expr->interpret() << std::endl; // Output: 15
  return 0;
}
