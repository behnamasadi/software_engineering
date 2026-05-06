// Interpreter — represent a grammar as classes, then evaluate.
//
// Expression           abstract; defines interpret()
//   Number             terminal: a literal value
//   BinaryOp           non-terminal: combines two sub-expressions
//     Add, Subtract    concrete operations
//
// Build the AST manually in main, then call interpret() on the root.

#include <iostream>
#include <memory>
#include <utility>

class Expression {
public:
    virtual ~Expression() = default;
    virtual int interpret() const = 0;
};

using ExprPtr = std::unique_ptr<Expression>;

class Number : public Expression {
public:
    explicit Number(int v) : value_(v) {}
    int interpret() const override { return value_; }
private:
    int value_;
};

class Add : public Expression {
public:
    Add(ExprPtr lhs, ExprPtr rhs) : lhs_(std::move(lhs)), rhs_(std::move(rhs)) {}
    int interpret() const override { return lhs_->interpret() + rhs_->interpret(); }
private:
    ExprPtr lhs_, rhs_;
};

class Subtract : public Expression {
public:
    Subtract(ExprPtr lhs, ExprPtr rhs) : lhs_(std::move(lhs)), rhs_(std::move(rhs)) {}
    int interpret() const override { return lhs_->interpret() - rhs_->interpret(); }
private:
    ExprPtr lhs_, rhs_;
};

int main() {
    // (5 + 10) - 3
    ExprPtr expr = std::make_unique<Subtract>(
        std::make_unique<Add>(std::make_unique<Number>(5), std::make_unique<Number>(10)),
        std::make_unique<Number>(3));

    std::cout << "(5 + 10) - 3 = " << expr->interpret() << '\n';
}
