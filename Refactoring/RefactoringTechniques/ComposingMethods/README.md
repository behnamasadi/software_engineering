# Composing Methods

Most of the refactoring is dedicated to writing methods correctly. In certain instances the source of all evil is unnecessarily long processes.
Within these systems, the vagaries of code obscure the execution logic and make the process incredibly difficult to understand — and much 
harder to modify.
Within this group, the refactoring techniques streamline processes, eliminate duplication of code and pave the way for future improvements.

## Extract Method
This refactoring helps you to construct a new method or feature locally based on the chosen code
Before refactoring:
```cpp
void printOwing()
{
  printBanner();

  // Print details.
  std::cout<<"name: " + name<<std::endl;
  std::cout<<"amount: " + getOutstanding()<<std::endl;
}
```

```cpp
void printOwing()
{
    printBanner();
    printDetails(getOutstanding());
}

After refactoring:

void printDetails(double outstanding)
{
    // Print details.
    std::cout<<"name: " + name<<std::endl;
    std::cout<<"amount: " + outstanding()<<std::endl;
}
```

## Inline Method
use Inline Method when someone is using too much indirection and it seems that every method does simple delegation to another method.
Before refactoring:

```cpp
void Draw()
{
    try { /*draw*/ }
    catch (Exception e)
    {
        LogError(e);
    }
}
void LogError(Exception e)
{
    File.Write("Exception.txt", e.toString());
}
```

After refactoring:

```cpp
void Draw()
{
    try { /*draw*/ }
    catch (Exception e)
    {
        File.Write("Exception.txt", e.toString());;
    }
}
```
## Extract Variable
You have an expression that is difficult to understand, Put the result of the expression or its sections in separate self-explanatory variables.
Before refactoring:
```cpp
void renderBanner() 
{
    if ((platform.toUpperCase().indexOf("MAC") > -1) &&  (browser.toUpperCase().indexOf("IE") > -1) &&  wasInitialized() && resize > 0 )
    {
    // do something
    }
}
```
After refactoring:
```cpp
void renderBanner() 
{
    bool isMacOs = platform.toUpperCase().indexOf("MAC") > -1;
    bool isIE = browser.toUpperCase().indexOf("IE") > -1;
    bool wasResized = resize > 0;
    
    if (isMacOs && isIE && wasInitialized() && wasResized) 
    {
    // do something
    }
}
```
## Inline Temp

You have a temporary variable allocated to a basic expression outcome and nothing more. Replace the expression itself with references to the variable.

Before refactoring:
```cpp
bool hasDiscount(Order order) 
{
    double basePrice = order.basePrice();
    return basePrice > 1000;
}

```
After refactoring:
```cpp
bool hasDiscount(Order order) 
{
    return order.basePrice() > 1000;
}
```


## Replace Temp with Query
The problem with temps is they're temporary and local. Since these can only be seen in
Temps tend to promote longer methods in the sense of the process in which they are used,
And that's the only way to get to temp. By replacing temp with method of query,
You can get any method in the class at the details. This helps more in getting cleaner
Replace Temp with Query often is a vital step before Extract Method. Local variables make it
difficult to extract, so replace as many variables as you can with queries.


Before refactoring:
```cpp
double calculateTotal() 
{
    double basePrice = quantity * itemPrice;
    if (basePrice > 1000) 
    {
        return basePrice * 0.95;
    }
    else 
    {
        return basePrice * 0.98;
    }
}
```
After refactoring:
```cpp
double calculateTotal() 
{
    if (basePrice() > 1000) 
    {
        return basePrice() * 0.95;
    }
    else 
    {
        return basePrice() * 0.98;
    }
}
double basePrice() 
{
    return quantity * itemPrice;
}

```


## Split Temporary Variable
You have a local variable that’s used to store various intermediate values inside a method. Use different variables for different values.
 Each variable should be responsible for only one particular thing.

Before refactoring:
```cpp
    double temp = 2 * (height + width);
    std::cout<<temp<<std::endl;
    temp = height * width;
    std::cout<<temp<<std::endl;
```
After refactoring:
```cpp
    double perimeter = 2 * (height + width);
    std::cout<<perimeter<<std::endl;
    double area = height * width;
    std::cout<<area<<std::endl;
```

## Remove Assignments to Parameters
First, if a parameter is passed via reference, then after the parameter value is changed inside the method, this value is passed to the argument that requested calling this method. Very often, this occurs accidentally and leads to unfortunate effects. Even if parameters are usually passed by value (and not by reference) in your programming language, this coding quirk may alienate those who are unaccustomed to it.

Second, multiple assignments of different values to a single parameter make it difficult for you to know what data should be contained in the parameter at any particular point in time. The problem worsens if your parameter and its contents are documented but the actual value is capable of differing from what is expected inside the method.

Before refactoring:
```cpp
int discount(int inputVal, int quantity)
{
    if (inputVal > 50) 
    {
        inputVal -= 2;
    }
  // ...
}
```
After refactoring:
```cpp
int discount(int inputVal, int quantity) 
{
    int result = inputVal;
    if (inputVal > 50) 
    {
        result -= 2;
    }
    // ...
}
```

## Replace Method with Method Object
You have a long method in which the local variables are so intertwined that you can’t apply Extract Method. Transform the method into a separate class so that the local variables become fields of the class. Then you can split the method into several methods within the same class.

Before refactoring:
```cpp

```
After refactoring:
```cpp

```


Before refactoring:
```cpp

```
After refactoring:
```cpp

```

