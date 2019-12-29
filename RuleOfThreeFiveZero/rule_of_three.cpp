#include <cstring>
#include <iostream>

/*
Rule of three
If a class requires a
user-defined destructor,
a user-defined copy constructor,
or a user-defined copy assignment operator,
it almost certainly requires all three.
*/


class rule_of_three
{
    char* cstring; // raw pointer used as a handle to a dynamically-allocated memory block

    void init(const char* s)
    {
        std::size_t n = std::strlen(s) + 1;
        cstring = new char[n];
        std::memcpy(cstring, s, n);
    }
 public:
    rule_of_three(const char* s = "")
    {
        init(s);
    }

    /* user-defined destructor */
    ~rule_of_three()
    {
        delete[] cstring;
    }


    /* Copy constructor */

    rule_of_three(const rule_of_three& other)
    {
        init(other.cstring);
    }

    /* Copy assignment (Assignment operator)  */
    rule_of_three& operator=(const rule_of_three& other)
    {
        if(this != &other) {
            delete[] cstring;  // deallocate
            init(other.cstring);
        }
        return *this;
    }

    char* getCstring()
    {
        return this->cstring;
    }

};


int main()
{

    {
        std::cout<< "===========================Copy assignment (Assignment operator)======================"<<std::endl;
        rule_of_three  rule_of_three_1("1");
        rule_of_three  rule_of_three_2("2");

        std::cout<< rule_of_three_1.getCstring()<<std::endl;
        std::cout<< rule_of_three_2.getCstring()<<std::endl;

        rule_of_three_1=rule_of_three_2;
        std::cout<<rule_of_three_1.getCstring() <<std::endl;
    }

    {
        std::cout<< "===========================Copy operator======================"<<std::endl;

        rule_of_three other("other");
        rule_of_three rule_of_three_1 = other;
        rule_of_three rule_of_three_2(other);

        std::cout<<rule_of_three_1.getCstring() <<std::endl;
        std::cout<<rule_of_three_2.getCstring() <<std::endl;



    }
}
