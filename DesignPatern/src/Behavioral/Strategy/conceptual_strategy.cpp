#include <iostream>
#include <memory>

class Strategy
{
public:
    void virtual solve()=0;
};

class ConcreteStrategy1: public Strategy
{
    void solve() override
    {
        std::cout<<"ConcreteStrategy1 solution" <<std::endl;
    }
};

class ConcreteStrategy2: public Strategy
{
    void solve() override
    {
        std::cout<<"ConcreteStrategy2 solution" <<std::endl;
    }
};

class Context
{
    Strategy *m_strategy;

public:
    Context(Strategy *strategy= nullptr):m_strategy(strategy){}
    void setStrategy(Strategy *strategy)
    {
        m_strategy=strategy;
    }

    void execute()
    {
        m_strategy->solve();
    }
};

int main()
{
    Strategy *strategy1=new ConcreteStrategy1;
    Strategy *strategy2=new ConcreteStrategy2;
    Context context(strategy1);
    context.execute();
    context.setStrategy(strategy2);
    context.execute();
}
