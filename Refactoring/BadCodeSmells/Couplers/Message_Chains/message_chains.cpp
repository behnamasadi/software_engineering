//curentCustomer.getAddress().getCountry().isInEurope();
namespace before {

class Country {
public:
    bool isInEurope()
    {
        return true;
    }
};

class Address {
    Country country;

public:
    Country getCountry()
    {
        return country;
    }
};
class Customer {
    Address address;

public:
    Address getAddress()
    {
        return address;
    }

    bool isInEurope()
    {
        return address.getCountry().isInEurope();
    }
};
}

namespace after {

class Country {
public:
    bool isInEurope()
    {
        return true;
    }
};

class Address {
    Country country;

public:
    Country getCountry()
    {
        return country;
    }

    bool isInEurope()
    {
        return country.isInEurope();
    }
};
class Customer {
    Address address;

public:
    Address getAddress()
    {
        return address;
    }

    bool isInEurope()
    {
        return address.isInEurope();
    }
};
}

int main()
{
    {
        using namespace before;
        Customer curentCustomer;
        curentCustomer.isInEurope();
    }

    {
        using namespace after;
        Customer curentCustomer;
        curentCustomer.isInEurope();
    }
}
