/*
Because the presence of a user-defined destructor, copy-constructor, or copy-assignment operator prevents
implicit definition of the move constructor and the move assignment operator, any class for which  move semantics
 are desirable, has to declare all five special member functions

destructor
copy constructor
copy assignment operator
move constructor
move assignment operator


Unlike Rule of Three, failing to provide move constructor and move assignment is usually not an error,
but a missed optimization opportunity.

*/
#include <cstring>
#include <utility>

class rule_of_five
{
    char* cstring; // raw pointer used as a handle to a dynamically-allocated memory block
 public:
    rule_of_five(const char* s = "")
    : cstring(nullptr)
    {
        if (s) {
            std::size_t n = std::strlen(s) + 1;
            cstring = new char[n];      // allocate
            std::memcpy(cstring, s, n); // populate
        }
    }

    ~rule_of_five()
    {
        delete[] cstring;  // deallocate
    }

    rule_of_five(const rule_of_five& other) // copy constructor
    : rule_of_five(other.cstring)
    {}

    rule_of_five(rule_of_five&& other) noexcept // move constructor
    : cstring(std::exchange(other.cstring, nullptr))
    {}

    rule_of_five& operator=(const rule_of_five& other) // copy assignment
    {
         return *this = rule_of_five(other);
    }

    rule_of_five& operator=(rule_of_five&& other) noexcept // move assignment
    {
        std::swap(cstring, other.cstring);
        return *this;
    }

    char* getCstring()
    {
        return this->cstring;
    }

// alternatively, replace both assignment operators with
//  rule_of_five& operator=(rule_of_five other) noexcept
//  {
//      std::swap(cstring, other.cstring);
//      return *this;
//  }
};


int main()
{

}
