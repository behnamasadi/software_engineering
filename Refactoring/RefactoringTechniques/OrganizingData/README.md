# Organizing Data
These refactoring techniques help with data handling, replacing primitives with rich class functionality.
Another important result is untangling of class associations, which makes classes more portable and reusable.

## Self Encapsulate Field
You use direct access to private fields **inside** a class. Create a getter and setter for the field, and use only them for accessing the field.
Sometimes directly accessing a private field inside a class just isn’t flexible enough. You want to be able to initiate a field value when
 the first query is made or perform certain operations on new values of the field when they’re assigned, or maybe do all this in various
 ways in subclasses.

Before:
```cpp
class Range
{
private:
    int low, high;
    bool includes(int arg)
    {
        return arg >= low && arg <= high;
    }
};
```


After:
```cpp
class Range
{
private:
    int low, high;
public:
    bool includes(int arg)
    {
        return arg >= getLow() && arg <= getHigh();
    }
    int getLow()
    {
        return low;
    }
    int getHigh()
    {
        return high;
    }
};
```


## Replace Data Value with Object
This refactoring is special case of **Extract Class**.
Often in early stages of development you make decisions about representing simple facts as
simple data items. As development proceeds you realize that those simple items aren't so simple
anymore. A telephone number may be represented as a string for a while, but later you realize
that the telephone needs special behavior for formatting, extracting the area code, and the like.
For one or two items you may put the methods in the owning object, but quickly the code smells
of duplication and feature envy. When the smell begins, turn the data value into an object.


Before:
```cpp
class Order
{
private:
    std::string customer;
//methods operating on customer 
};
```

After:
```cpp
class Customer
{
    std::string customer;
    //methods operating on customer
};

class Order
{
private:
    Customer customer;
};
```

## Change Value to Reference
Each order has its own customer object even if they are for the same conceptual customer. I want to change this so that if we have several orders for the same conceptual customer, they share a single customer object. For this case this means that there should be only one customer object for each 
customer name.

Before:
```cpp
class Customer
{
private:
    std::string m_name;
public:
    Customer (std::string name)
    {
        m_name = name;
    };
    std::string getName()
    {
        return m_name;
    }
};

class Order
{
private:
    Customer * m_customer;
public:
    Order (std::string customerName)
    {
        m_customer = new Customer(customerName);
    }
    void setCustomer(std::string customerName)
    {
        m_customer = new Customer(customerName);
    }
    std::string getCustomerName()
    {
        return m_customer->getName();
    }
};


int numberOfOrdersFor(std::vector<Order> orders , std::string customer)
{
    int result = 0;
    for(std::vector<Order>::iterator iter = orders.begin();iter!=orders.end();iter++)
    {

        if (iter->getCustomerName().compare(customer)== 0)
            result++;
    }
return result;
}
```
Firstyou have to begin by using **Replace Constructor with Factory Method**. This allows you to take control of the creation process, 
which will become important later. 
1) Define the factory method on customer.
2) Replace the calls to the constructor with calls to the factory.
3) Make the constructor private.


Now you have to decide how to access the customers. My preference is to use another object. Such
a situation works well with something like the line items on an order. The order is responsible for
providing access to the line items. However, in this situation there isn't such an obvious object. In
this situation I usually create a registry object to be the access point. For simplicity in this
example, however, I store them using a static field on customer, making the customer class the
access point:




After:
```cpp
class Customer
{
private:
    std::string m_name;
    Customer (std::string name)
    {
        m_name = name;
    }

    void store()
    {
        m_instances.insert(std::make_pair(this->getName(), this));
    }

    static std::map<std::string, Customer* > m_instances;
public:

    static void loadCustomers()
    {
        (new Customer("Lemon Car Hire"))->store();
        (new Customer ("Associated Coffee Machines"))->store();
        (new Customer ("Bilston Gasworks"))->store();
    }

    static Customer *create (std::string name)
    {
        return  m_instances[name];
    }

    std::string getName()
    {
        return m_name;
    }


    static Customer * getNamed (std::string name)
    {
        return m_instances[name];
    }
};


class Order
{
private:
    Customer * m_customer;
public:
    Order (std::string customer)
    {
        m_customer = Customer::create(customer);
    }
};

```


## Change Reference to Value

Before:
```cpp
```


After:
```cpp
```

## Replace Array with Object
You have an array that contains various types of data. Replace the array with an object that will have separate fields for each element.
 if you use an array like post office boxes, storing the username in box 1 and the user’s address in box 14, you will someday be very unhappy 
that you did. This approach leads to catastrophic failures when somebody puts something in the wrong “box” and also requires your time for 
figuring out which data is stored where.


Before:
```cpp
std::string *row = new std::string[2];
    row[0] = "Liverpool";
    row[1] = "15";
```


After:
```cpp
Performance *row = new Performance();
    row->setName("Liverpool");
    row->setWins("15");
```


## Duplicate Observed Data

Imagine a registration form, where there are input fields like username, email, phone number and password. We can have some logic that enable/ disable
 the Register button until all fields are filled and the phone number and email valid. We can of course put everything in the 
UI form, but if you want to have multiple interface views for the same data (for example, you have both a desktop app and a mobile app) you will u fail to separate the GUI from the domain, you will have a very hard time avoiding code duplication and a large number of mistakes.
So we create a new RegisterModel class, create 4 private String fields - username, email, phone number and password. Then we create getter 
and setter for these fields. When in the Activity the user changed one of the fields, we directly call the corresponding setter function 
in the model, and the model can do the calculation and validation and whatnot, then use some PubSub mechanism to notify the view.


## Change Unidirectional Association to Bidirectional
You have two classes that each need to use the features of the other, but the association between them is only unidirectional. Add the missing
 association to the class that needs it. Originally the classes had a unidirectional association. But with time, client code needed access to 
both sides of the association.

Before:
```cpp
class Customer{};

class Order
{
    Customer m_customer;
public:
    Customer getCustomer() 
    {
        return m_customer;
    }
    void setCustomer (Customer arg) 
    {
        m_customer = arg;
    }
};
```
The customer class has no reference to the order. You need to decide which class will take charge of the association.

1. If both objects are reference objects and the association is one to many, then the object
that has the one reference is the controller. (That is, if one customer has many orders,
the order controls the association.)
2. If one object is a component of the other, the composite should control the association.
3. If both objects are reference objects and the association is many to many, it doesn't
matter whether the order or the customer controls the association.

After:
```cpp

```


## 

Before:
```cpp
```


After:
```cpp
```


## 

Before:
```cpp
```


After:
```cpp
```


## 

Before:
```cpp
```


After:
```cpp
```


## 

Before:
```cpp
```


After:
```cpp
```


## 

Before:
```cpp
```


After:
```cpp
```

## 

Before:
```cpp
```


After:
```cpp
```

