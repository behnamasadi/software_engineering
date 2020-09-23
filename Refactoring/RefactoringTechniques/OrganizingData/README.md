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
This refactoring is special case of **Extract Class**

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

