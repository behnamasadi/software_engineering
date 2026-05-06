// Visitor — operation that walks a tree without changing the node classes.
// Each Expression node has accept(visitor); the visitor decides per node type
// what to do. Adding a new operation = a new visitor; node classes don't change.

#include <iostream>
#include <memory>
#include <string>
#include <utility>

class Literal;
class Addition;

class ExpressionVisitor {
public:
    virtual ~ExpressionVisitor() = default;
    virtual void visit(const Literal& literal) = 0;
    virtual void visit(const Addition& addition) = 0;
};

class Expression {
public:
    virtual ~Expression() = default;
    virtual void accept(ExpressionVisitor& visitor) const = 0;
};

class Literal : public Expression {
public:
    explicit Literal(double value) : value_(value) {}
    double value() const { return value_; }
    void accept(ExpressionVisitor& visitor) const override { visitor.visit(*this); }
private:
    double value_;
};

class Addition : public Expression {
public:
    Addition(std::unique_ptr<Expression> lhs, std::unique_ptr<Expression> rhs)
        : left_(std::move(lhs)), right_(std::move(rhs)) {}

    const Expression& left()  const { return *left_; }
    const Expression& right() const { return *right_; }

    void accept(ExpressionVisitor& visitor) const override { visitor.visit(*this); }

private:
    std::unique_ptr<Expression> left_, right_;
};

class ExpressionPrinter : public ExpressionVisitor {
public:
    void visit(const Literal& literal) override {
        out_ += std::to_string(literal.value());
    }
    void visit(const Addition& addition) override {
        out_ += "(";
        addition.left().accept(*this);
        out_ += " + ";
        addition.right().accept(*this);
        out_ += ")";
    }

    const std::string& result() const { return out_; }

private:
    std::string out_;
};

int main() {
    // (1 + 2) + 3
    auto expr = std::make_unique<Addition>(
        std::make_unique<Addition>(std::make_unique<Literal>(1), std::make_unique<Literal>(2)),
        std::make_unique<Literal>(3));

    ExpressionPrinter printer;
    expr->accept(printer);
    std::cout << printer.result() << '\n';
}
