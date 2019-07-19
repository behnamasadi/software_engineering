//https://www.youtube.com/watch?v=ANXPjR5lKTE
#include <iostream>
#include <functional>

namespace before
{

class robot
{
public:
    virtual void search()=0;
    virtual void attack()=0;
    virtual void defend()=0;
    virtual ~robot()=default;
};

class linear : public robot
{
public:
    void search()
    {
        std::cout<<"linear" <<std::endl;
    }
};

class linearPinch : public linear
{
public:
    void attack()
    {
        std::cout<<"pinch" <<std::endl;

    }
};

class linearPinchRun: public linearPinch
{
public:
    void defend()
    {
        std::cout<<"run" <<std::endl;
    }

};

class linearPunch : public linear
{
public:
    void attack()
    {
        std::cout<<"punch" <<std::endl;

    }
};

class linearPunchRun: public linearPunch
{
public:
    void defend()
    {
        std::cout<<"run" <<std::endl;
    }

};

class spiral: public robot
{
    void search()
    {
        std::cout<<"spiral" <<std::endl;
    }
};

class spiralPinch:public spiral
{
public:
    void attack()
    {
        std::cout<<"pinch" <<std::endl;

    }
};

class spiralPinchRun:public spiralPinch
{
    void defend()
    {
        std::cout<<"run" <<std::endl;
    }
};



}

//runtime polymorphism
namespace after
{

class robot;

class Search
{
public:
    virtual void apply(robot* r)=0;
    virtual~Search()=default;
};

class Attack
{
public:
    virtual void apply(robot* r)=0;
    virtual~Attack()=default;
};

class Defend
{
public:
    virtual void apply(robot *r)=0;
    virtual~Defend()=default;
};

class robot
{
    Search* m_search;
    Attack* m_attack;
    Defend* m_defend;
public:
    robot(Search* search ,Attack* attack,Defend* defend):m_search(search) ,m_attack(attack) ,m_defend(defend) {}

    void attack()
    {
        m_attack->apply(this);
    }
    void defend()
    {
        m_defend->apply(this);
    }
    void search()
    {
        m_search->apply(this);
    }

};

class linear:public Search
{
    void apply(robot *r)
    {
        std::cout<<"search(linear)" <<std::endl;
    }
};

class spiral:public Search
{
    void apply(robot *r)
    {
        std::cout<<"spiral(linear)" <<std::endl;
    }
};

class punch:public Attack
{
    void apply(robot *r)
    {
        std::cout<<"punch(attack)" <<std::endl;
    }
};

class pinch:public Attack
{
    void apply(robot *r)
    {
        std::cout<<"punch(attack)" <<std::endl;
    }
};

class run:public Defend
{
    void apply(robot *r)
    {
        std::cout<<"run(defend)" <<std::endl;
    }
};

}


//compile time polymorphism
namespace functionPtr
{

class robot
{
    public:
    using Search=std::function<void(robot*)>;
    using Attack=std::function<void(robot*)>;
    using Defend=std::function<void(robot*)>;

    Search m_search;
    Attack m_attack;
    Defend m_defend;


    robot(Search  search ,Attack  attack,Defend defend):m_search(search) ,m_attack(attack) ,m_defend(defend) {}
    void attack()
    {
       m_attack(this);
    }
    void defend()
    {
       m_defend(this);
    }
    void search()
    {
      m_search(this);
    }

};

class Search
{
public:

    void operator()(robot *r)
    {
        std::cout<<"Search" <<std::endl;
    }
};

class  Attack
{
public:

    void operator()(robot *r)
    {
        std::cout<<"punch" <<std::endl;
    }
};

class  Defend
{
public:
    void operator()(robot *r)
    {
        std::cout<<"run" <<std::endl;
    }
};



}



template <typename T>
void go(T *r)
{
    r->search();
    r->attack();
    r->defend();
}

int main()
{
    {
        before::robot * r1=new before::linearPinchRun;
        go(r1);
        before::robot * r2=new before::linearPunchRun;
        go(r2);
        before::robot * r3=new before::spiralPinchRun;
        go(r3);
    }


    {

        after::Attack *punch=new after::punch();
        after::Attack *pinch=new after::pinch();
        after::Search *linearsearch=new after::linear();
        after::Search *spiralsearch=new after::spiral();
        after::Defend *defend=new after::run();
        after::robot *r1=new after::robot(linearsearch,punch,defend);
        after::robot *r2=new after::robot(linearsearch,pinch,defend);
        after::robot *r3=new after::robot(spiralsearch,pinch,defend);

        go(r1);
        go(r2);
        go(r3);

    }

    {
        functionPtr::Attack punch;
        functionPtr::Search linearsearch;
        functionPtr::Defend defend;
        functionPtr::robot r1(linearsearch,punch,defend);
        go(&r1);

        functionPtr::robot r2(linearsearch,punch, [](functionPtr::robot* r){std::cout<<"hide\n";} );
        go(&r2);
    }

}
