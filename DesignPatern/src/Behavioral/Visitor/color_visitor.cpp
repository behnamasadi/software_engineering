#include <iostream>
using namespace std;

namespace before
{
class Color
{
  public:
    virtual void count() = 0;
    virtual void call() = 0;
    static void report_num()
    {
        cout << "Reds " << s_num_red << ", Blus " << s_num_blu << '\n';
    }
  protected:
    static int s_num_red, s_num_blu;
};
int Color::s_num_red = 0;
int Color::s_num_blu = 0;

class Red: public Color
{
  public:
    void count()
    {
        ++s_num_red;
    }
    void call()
    {
        eye();
    }
    void eye()
    {
        cout << "Red::eye\n";
    }
};

class Blu: public Color
{
  public:
    void count()
    {
        ++s_num_blu;
    }
    void call()
    {
        sky();
    }
    void sky()
    {
        cout << "Blu::sky\n";
    }
};
}

namespace after
{
class Color
{
  public:
    virtual void accept(class Visitor*) = 0;
};

class Red: public Color
{
  public:
     /*virtual*/void accept(Visitor*);
    void eye()
    {
        cout << "Red::eye\n";
    }
};
class Blu: public Color
{
  public:
     /*virtual*/void accept(Visitor*);
    void sky()
    {
        cout << "Blu::sky\n";
    }
};

class Visitor
{
  public:
    virtual void visit(Red*) = 0;
    virtual void visit(Blu*) = 0;
};

class CountVisitor: public Visitor
{
  public:
    CountVisitor()
    {
        m_num_red = m_num_blu = 0;
    }
     /*virtual*/void visit(Red*)
    {
        ++m_num_red;
    }
     /*virtual*/void visit(Blu*)
    {
        ++m_num_blu;
    }
    void report_num()
    {
        cout << "Reds " << m_num_red << ", Blus " << m_num_blu << '\n';
    }
  private:
    int m_num_red, m_num_blu;
};

class CallVisitor: public Visitor
{
  public:
     /*virtual*/void visit(Red *r)
    {
        r->eye();
    }
     /*virtual*/void visit(Blu *b)
    {
        b->sky();
    }
};

void Red::accept(Visitor *v)
{
  v->visit(this);
}

void Blu::accept(Visitor *v)
{
  v->visit(this);
}
}

int main()
{

    {
        using namespace before;
        Color *set[] ={new Red, new Blu, new Blu, new Red, new Red, 0 };
        for (int i = 0; set[i]; ++i)
        {
          set[i]->count();
          set[i]->call();
        }
        Color::report_num();
    }


    {
    using namespace after;

        Color *set[] = { new Red, new Blu, new Blu, new Red, new Red, 0 };
        CountVisitor count_operation;
        CallVisitor call_operation;
        for (int i = 0; set[i]; i++)
        {
            set[i]->accept(&count_operation);
            set[i]->accept(&call_operation);
        }
        count_operation.report_num();
    }
}

