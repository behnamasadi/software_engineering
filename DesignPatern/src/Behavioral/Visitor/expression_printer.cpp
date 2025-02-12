#include <iostream>
#include <memory>
#include <string>

class Literal;
class Addition;

class IExpressionVisitor {
public:
    virtual ~IExpressionVisitor() = default;
    virtual void Visit(const Literal& literal) = 0;
    virtual void Visit(const Addition& addition) = 0;
};

class IExpression {
public:
    virtual ~IExpression() = default;
    virtual void Accept(IExpressionVisitor& visitor) const = 0;
};

class Literal : public IExpression {
public:
    double value;
    explicit Literal(double val) : value(val) {}
    void Accept(IExpressionVisitor& visitor) const override {
        visitor.Visit(*this);
    }
};

class Addition : public IExpression {
public:
    std::unique_ptr<IExpression> left;
    std::unique_ptr<IExpression> right;

    Addition(std::unique_ptr<IExpression> lhs, std::unique_ptr<IExpression> rhs)
        : left(std::move(lhs)), right(std::move(rhs)) {}

    void Accept(IExpressionVisitor& visitor) const override {
        visitor.Visit(*this);
    }
};

class ExpressionPrinter : public IExpressionVisitor {
    std::string output;

public:
    void Visit(const Literal& literal) override {
        output += std::to_string(literal.value);
    }

    void Visit(const Addition& addition) override {
        output += "(";
        addition.left->Accept(*this);
        output += " + ";
        addition.right->Accept(*this);
        output += ")";
    }

    std::string GetResult() const {
        return output;
    }
};

int main() {
    // Construct (1 + 2) + 3 using smart pointers
    auto expr = std::make_unique<Addition>(
        std::make_unique<Addition>(std::make_unique<Literal>(1), std::make_unique<Literal>(2)),
        std::make_unique<Literal>(3)
    );

    ExpressionPrinter printer;
    expr->Accept(printer);
    
    std::cout << printer.GetResult() << std::endl;
}
