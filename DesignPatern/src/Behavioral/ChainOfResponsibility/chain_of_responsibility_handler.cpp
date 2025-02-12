#include <iostream>
#include <vector>
#include <ctime>

using namespace std;

class Base {
public:
    Base* next; // 1. "next" pointer in the base class

    Base() : next(nullptr) {}

    void setNext(Base* n) {
        next = n;
    }

    void add(Base* n) {
        if (next)
            next->add(n);
        else
            next = n;
    }

    // 2. The "chain" method in the base class always delegates to the next obj
    virtual void handle(int i) {
        if (next)
            next->handle(i); // Check for null before calling
        else
            cout << "No handler could process " << i << '\n';
    }

    virtual ~Base() = default; // Virtual destructor for proper cleanup
};

class Handler1 : public Base {
public:
    void handle(int i) override {
        if (i % 4 == 1) {
            cout << "H1 handled " << i << "  ";
        } else {
            cout << "H1 passed " << i << "  ";
            if (next) next->handle(i);
        }
    }
};

class Handler2 : public Base {
public:
    void handle(int i) override {
        if (i % 4 == 2) {
            cout << "H2 handled " << i << "  ";
        } else {
            cout << "H2 passed " << i << "  ";
            if (next) next->handle(i);
        }
    }
};

class Handler3 : public Base {
public:
    void handle(int i) override {
        if (i % 4 == 3) {
            cout << "H3 handled " << i << "  ";
        } else {
            cout << "H3 passed " << i << "  ";
            if (next) next->handle(i);
        }
    }
};

class Handler4 : public Base {
public:
    void handle(int i) override {
        if (i % 4 == 0) {
            cout << "H4 handled " << i << "  ";
        } else {
            cout << "H4 passed " << i << "  ";
            if (next) next->handle(i);
        }
    }
};

int main() {
    srand(time(0));

    Handler1 root;
    Handler2 two;
    Handler3 thr;
    Handler4 four;

    root.add(&two);
    root.add(&thr);
    root.add(&four);

    // Removed circular reference: `four.setNext(&root);`

    for (int i = 0; i < 9; i++) {
        root.handle(i);
        cout << '\n';
    }

    return 0;
}
