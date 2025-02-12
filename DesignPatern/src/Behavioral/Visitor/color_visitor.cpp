#include <iostream>
using namespace std;

namespace before
{
class Color
{
  public:
    virtual void count() = 0;
    virtual void call() = 0;
    static void report_statistics()
    {
        cout << "Red count: " << s_num_red << ", Blue count: " << s_num_blu << '\n';
    }
  protected:
    static int s_num_red, s_num_blu;
};
int Color::s_num_red = 0;
int Color::s_num_blu = 0;

class Red: public Color
{
  public:
    void count() override
    {
        ++s_num_red;
    }
    void call() override
    {
        showEye();
    }
    void showEye()
    {
        cout << "Red::showEye\n";
    }
};

class Blu: public Color
{
  public:
    void count() override
    {
        ++s_num_blu;
    }
    void call() override
    {
        showSky();
    }
    void showSky()
    {
        cout << "Blu::showSky\n";
    }
};
}

namespace after
{
class Visitor;

class Color
{
  public:
    virtual void accept(Visitor*) = 0;
};

class Red: public Color
{
  public:
    void accept(Visitor*) override;
    void showEye()
    {
        cout << "Red::showEye\n";
    }
};

class Blu: public Color
{
  public:
    void accept(Visitor*) override;
    void showSky()
    {
        cout << "Blu::showSky\n";
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
    CountVisitor() : m_num_red(0), m_num_blu(0) {}
    void visit(Red*) override
    {
        ++m_num_red;
    }
    void visit(Blu*) override
    {
        ++m_num_blu;
    }
    void report_statistics()
    {
        cout << "Red count: " << m_num_red << ", Blue count: " << m_num_blu << '\n';
    }
  private:
    int m_num_red, m_num_blu;
};

class CallVisitor: public Visitor
{
  public:
    void visit(Red *r) override
    {
        r->showEye();
    }
    void visit(Blu *b) override
    {
        b->showSky();
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
        Color *set[] ={new Red, new Blu, new Blu, new Red, new Red, nullptr };
        for (int i = 0; set[i]; ++i)
        {
          set[i]->count();
          set[i]->call();
        }
        Color::report_statistics();
    }

    {
        using namespace after;
        Color *set[] = { new Red, new Blu, new Blu, new Red, new Red, nullptr };
        CountVisitor count_operation;
        CallVisitor call_operation;
        for (int i = 0; set[i]; i++)
        {
            set[i]->accept(&count_operation);
            set[i]->accept(&call_operation);
        }
        count_operation.report_statistics();
    }
}
