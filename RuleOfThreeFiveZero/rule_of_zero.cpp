/*
Rule of zero
Classes that have custom destructors, copy/move constructors or copy/move assignment operators
should deal exclusively with ownership. Other classes should not have custom destructors,
copy/move constructors or copy/move assignment operators.
*/

#include <string>

class rule_of_zero
{
    std::string cppstring;
 public:
    rule_of_zero(const std::string& arg) : cppstring(arg) {}
};

/*
When a base class is intended for polymorphic use, its destructor may have to be declared public and virtual.
This blocks implicit moves (and deprecates implicit copies), and so the special member functions have to be
declared as defaulted
*/

class base_of_five_defaults
{
 public:
    base_of_five_defaults(const base_of_five_defaults&) = default;
    base_of_five_defaults(base_of_five_defaults&&) = default;
    base_of_five_defaults& operator=(const base_of_five_defaults&) = default;
    base_of_five_defaults& operator=(base_of_five_defaults&&) = default;
    virtual ~base_of_five_defaults() = default;
};


class foo
{
public:

/*
=0
C++ uses the special syntax = 0; to indicate pure virtual functions instead of adding a new keyword to the language
*/
    void virtual pureVirtualFunction()=0;
/*
=default
It means that you want to use the compiler-generated version of that function, so you don't need to specify a body.
*/
    ~foo()=default;
/*
= delete
    It means that the compiler will not generate those constructors for you. This is only allowed on copy constructor and assignment operator
*/
    foo(const foo &t) = delete;
    foo& operator = (const foo &t)= delete ;
};


int main()
{

}
