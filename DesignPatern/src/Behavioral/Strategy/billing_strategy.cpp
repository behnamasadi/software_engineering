#include <iostream>
#include <memory>
#include <string>
#include <vector>

class Literal;
class Addition;

class IExpressionVisitor {
public:
    virtual ~IExpressionVisitor() = default;
    virtual void Visit(const Literal &literal) = 0;
    virtual void Visit(const Addition &addition) = 0;
};

class IExpression {
public:
    virtual ~IExpression() = default;
    virtual void Accept(IExpressionVisitor &visitor) const = 0;
};

class Literal : public IExpression {
public:
    double value;

    explicit Literal(double val) : value(val) {}

    void Accept(IExpressionVisitor &visitor) const override {
        visitor.Visit(*this);
    }
};

class Addition : public IExpression {
public:
    std::unique_ptr<IExpression> left;
    std::unique_ptr<IExpression> right;

    Addition(std::unique_ptr<IExpression> l, std::unique_ptr<IExpression> r)
        : left(std::move(l)), right(std::move(r)) {}

    void Accept(IExpressionVisitor &visitor) const override {
        visitor.Visit(*this);
    }
};

class ExpressionPrinter : public IExpressionVisitor {
    std::string result;

public:
    void Visit(const Literal &literal) override {
        result += std::to_string(literal.value);
    }

    void Visit(const Addition &addition) override {
        result += "(";
        addition.left->Accept(*this);
        result += " + ";
        addition.right->Accept(*this);
        result += ")";
    }

    std::string GetResult() const {
        return result;
    }
};

int main() {
    // Constructing the expression (1 + 2) + 3
    auto expression = std::make_unique<Addition>(
        std::make_unique<Addition>(
            std::make_unique<Literal>(1),
            std::make_unique<Literal>(2)),
        std::make_unique<Literal>(3));

    ExpressionPrinter printer;
    expression->Accept(printer);

    std::cout << printer.GetResult() << std::endl;

    return 0;
}
