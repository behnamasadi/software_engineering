#include <iostream>
namespace before {

class Phone {
private:
    std::string unformattedNumber;

public:
    Phone(std::string unformattedNumber)
    {
        this->unformattedNumber = unformattedNumber;
    }
    std::string getAreaCode()
    {
        return unformattedNumber.substr(0, 3);
    }
    std::string getPrefix()
    {
        return unformattedNumber.substr(3, 6);
    }

    std::string getNumber()
    {
        return unformattedNumber.substr(6, 10);
    }
};

class Customer {
private:
    Phone mobilePhone;

public:
    //Customer reaches into Phone’s data to format the number Feature Envy often shows up as a misplaced responsibility.
    std::string getMobilePhoneNumber()
    {
        return "(" + mobilePhone.getAreaCode() + ") " + mobilePhone.getPrefix() + "-" + mobilePhone.getNumber();
    }
};
}

namespace after {

class Phone {
private:
    std::string unformattedNumber;

public:
    Phone(std::string unformattedNumber)
    {
        this->unformattedNumber = unformattedNumber;
    }
    std::string getAreaCode()
    {
        return unformattedNumber.substr(0, 3);
    }
    std::string getPrefix()
    {
        return unformattedNumber.substr(3, 6);
    }
    std::string getNumber()
    {
        return unformattedNumber.substr(6, 10);
    }
    std::string toFormattedString()
    {
        return "(" + getAreaCode() + ") " + getPrefix() + "-" + getNumber();
    }
};
class Customer {
private:
    Phone mobilePhone;

public:
    //Now Customer relies on Phone to do the formatting.
    std::string getMobilePhoneNumber()
    {
        return mobilePhone.toFormattedString();
    }
};
}

int main()
{
}
