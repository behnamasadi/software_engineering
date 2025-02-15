#include <iostream>
#include <memory>
#include <mutex>

using namespace std;

namespace before {
class GlobalClass {
    int m_value;
public:
    explicit GlobalClass(int v = 0) : m_value(v) {}
    int get_value() const { return m_value; }
    void set_value(int v) { m_value = v; }
};

// Default initialization using smart pointer
std::unique_ptr<GlobalClass> global_ptr;

void foo() {
    if (!global_ptr)
        global_ptr = std::make_unique<GlobalClass>();
    global_ptr->set_value(1);
    cout << "foo: global_ptr is " << global_ptr->get_value() << '\n';
}

void bar() {
    if (!global_ptr)
        global_ptr = std::make_unique<GlobalClass>();
    global_ptr->set_value(2);
    cout << "bar: global_ptr is " << global_ptr->get_value() << '\n';
}
}

namespace after {
class GlobalClass {
    int m_value;
    static std::unique_ptr<GlobalClass> s_instance;
    static std::mutex mtx;

    explicit GlobalClass(int v = 0) : m_value(v) {}

public:
    int get_value() const { return m_value; }
    void set_value(int v) { m_value = v; }

    static GlobalClass* instance() {
        std::lock_guard<std::mutex> lock(mtx);
        if (!s_instance) {
            s_instance.reset(new GlobalClass());  // Fixed: Using reset() instead of make_unique()
        }
        return s_instance.get();
    }
};

// Initialize static members
std::unique_ptr<GlobalClass> GlobalClass::s_instance;
std::mutex GlobalClass::mtx;

void foo() {
    GlobalClass::instance()->set_value(1);
    cout << "foo: global_ptr is " << GlobalClass::instance()->get_value() << '\n';
}

void bar() {
    GlobalClass::instance()->set_value(2);
    cout << "bar: global_ptr is " << GlobalClass::instance()->get_value() << '\n';
}
}

int main() {
    {
        if (!before::global_ptr)
            before::global_ptr = std::make_unique<before::GlobalClass>();
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
