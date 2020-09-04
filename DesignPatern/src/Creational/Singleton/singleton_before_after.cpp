#include <iostream>

using namespace std;

namespace before
{
class GlobalClass
{
    int m_value;
  public:
    GlobalClass(int v = 0)
    {
        m_value = v;
    }
    int get_value()
    {
        return m_value;
    }
    void set_value(int v)
    {
        m_value = v;
    }
};

// Default initialization
GlobalClass *global_ptr = 0;

void foo(void)
{
  // Initialization on first use
  if (!global_ptr)
    global_ptr = new GlobalClass;
  global_ptr->set_value(1);
  cout << "foo: global_ptr is " << global_ptr->get_value() << '\n';
}

void bar(void)
{
  if (!global_ptr)
    global_ptr = new GlobalClass;
  global_ptr->set_value(2);
  cout << "bar: global_ptr is " << global_ptr->get_value() << '\n';
}

}


namespace after
{
class GlobalClass
{
    int m_value;
    static GlobalClass *s_instance;
    GlobalClass(int v = 0)
    {
        m_value = v;
    }
    public:
    int get_value()
    {
        return m_value;
    }
    void set_value(int v)
    {
        m_value = v;
    }
    static GlobalClass *instance()
    {
        if (!s_instance)
          s_instance = new GlobalClass;
        return s_instance;
    }
};

// Allocating and initializing GlobalClass's
// static data member.  The pointer is being
// allocated - not the object inself.
GlobalClass *GlobalClass::s_instance = 0;

void foo(void)
{
    GlobalClass::instance()->set_value(1);
    cout << "foo: global_ptr is " << GlobalClass::instance()->get_value() << '\n';
}

void bar(void)
{
    GlobalClass::instance()->set_value(2);
    cout << "bar: global_ptr is " << GlobalClass::instance()->get_value() << '\n';
}


}

int main()
{
    {
        if (!before::global_ptr)
            before::global_ptr = new before::GlobalClass;
        cout << "main: global_ptr is " << before::global_ptr->get_value() << '\n';
        before::foo();
        before::bar();
    }


    {
        cout << "main: global_ptr is " << after::GlobalClass::instance()->get_value() << '\n';
        after::foo();
        after::bar();
    }

}
