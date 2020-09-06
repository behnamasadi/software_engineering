/*
src: https://sourcemaking.com/design_patterns/adapter/cpp/2
*/
#include <iostream>

class LegecyRectangle
{
public:
    void draw()
    {
        std::cout<<"Legecy Rectangle draw()" <<std::endl;
    }
};

class LegecyCircle
{
public:
    void draw()
    {
        std::cout<<"Legecy Circle draw()" <<std::endl;
    }
};

class ExecuteInterface
{
public:
    virtual ~ExecuteInterface(){};
    virtual void execute()=0;
};

template<class ClassType>
class ExecuteAdapter:public ExecuteInterface
{
    ClassType *m_object ;
/*
    Here we are declaring a function with the signature void (funcname)() that should come from a clas called ClassType
*/
    void (ClassType:: *m_method)();

public:
    ExecuteAdapter(ClassType *object ,void (ClassType:: *method)() )
    {
       m_object=object;
       m_method=method;
    }

    void execute() override
    {
        (m_object->*m_method)();
    }
    ~ExecuteAdapter()
    {
          delete m_object;
    }
};

int main()
{
    ExecuteInterface *shape1=new ExecuteAdapter<LegecyRectangle>(new LegecyRectangle(), &LegecyRectangle::draw);
    shape1->execute();

    ExecuteInterface *shape2=new ExecuteAdapter<LegecyCircle>(new LegecyCircle(), &LegecyCircle::draw);
    shape2->execute();
}
