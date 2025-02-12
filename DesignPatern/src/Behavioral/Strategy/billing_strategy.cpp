/*
*/
#include <string>
#include <iostream>
#include <vector>

class Literal;
class Addition;

class IExpressionVisitor
{
    public:
    void Visit(Literal *literal){}
    void Visit(Addition *addition){}
};

class IExpression
{
public:
    void Accept(IExpressionVisitor *visitor);
};

class Literal :public IExpression
{
public:
    double Value;

    Literal(double value)
    {
      this->Value = value;
    }
    void Accept(IExpressionVisitor *visitor)
    {
      visitor->Visit(this);
    }
};

class Addition :public IExpression
{
public:
    IExpression *Left;
    IExpression *Right;

    Addition(IExpression *left, IExpression *right)
    {
        this->Left = left;
        this->Right = right;
    }

    void Accept(IExpressionVisitor *visitor)
    {
        visitor->Visit(this);
    }
};

class ExpressionPrinter :public IExpressionVisitor
{
    std::string sb;

public:
    ExpressionPrinter(std::string sb)
    {
        this->sb = sb;
    }

    void Visit(Literal *literal)
    {
        sb.append(std::to_string(literal->Value) );
    }

    void Visit(Addition *addition)
    {
        sb.append("(");
        addition->Left->Accept(this);
        sb.append("+");
        addition->Right->Accept(this);
        sb.append(")");
    }
};

int main()
{
    // emulate 1+2+3
    auto e = new Addition( new Addition( new Literal(1),  new Literal(2) ), new Literal(3) );
    std::string sb;
    IExpressionVisitor * expressionPrinter = new ExpressionPrinter(sb);
    e->Accept(expressionPrinter);
    std::cout<< sb<<std::endl;
}