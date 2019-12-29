#include <algorithm>
#include <vector>
#include <iostream>
#include <memory>
#include <string>
#include <exception>

/*
Book: Refactoring: Improving the Design of Existing Code

ref: https://www.youtube.com/watch?v=4F72VULWFvc

Tips in clean code, refactoring:



1) ====================== Null Object ======================
Never return null, instead return null object, i.e empty list. for instance a logger
which might retrun nothing.
fine line between multiple if and hirechechy inheritence
2) ====================== Returning Error ======================
Don't return error instead throw exceptin

3) ====================== Conditionals With Composition ======================
Many if could be avoid with polymorphism where busines logic should behave differntly. Usually switch
statment are sign for polymorphism repeated condition. Where the business logic needs if use interface,
use if only when comparing numbers.
Less if less easier testing. Replace Conditional With polymorphism State/Strategy and Replace Conditional With Polymorphism.
If you have a field in your object and besed on the content of that if you code behave differently,
put the common logic in super class and specific behaviour into subclass

Example, we have mathematical expression like this:

    1+2*3

and we want to represent this as tree:

         +
        / \
       1   *
          / \
         2   3

so we want to have evaluate() method that give us the the result of expression
The following implementation has some problem:
1) Leaf node have left and right child while they are only some numbers.
2) Operation node such as +,* they don't need value.
So here we can see depending on some if our class, behave differently.

*/


namespace before
{
class Node
{
public:
    char option;
    double value;
    Node * left;
    Node * right;

    double evaluate()
    {
        switch (option)
        {
        case '#': return value;
            break;
        case '+': return left->evaluate()+right->evaluate();
            break;
        case '*': return left->evaluate()*right->evaluate();
            break;

        default:
            break;
        }
    }
};
}
/*
Here we broke the code into value and operation node
*/
namespace after
{
class Node
{
public:
    virtual double evaluate()=0;
};

class ValueNode: public Node
{
public:
    double value;
    double evaluate()
    {
        return value;
    }
};

class OpNode:public Node
{
public:
    Node* left, *right;
    double evaluate()=0;
};

class AdditionNode:public OpNode
{
public:
    double evaluate()
    {
        return left->evaluate()+right->evaluate();
    }
};

class Multipication:public OpNode
{
public:
    double evaluate()
    {
        return left->evaluate()*right->evaluate();
    }
};





}


namespace before
{

enum class BIRD : unsigned char
{
    EUROPEAN,
    AFRICAN,
    NORWEGIAN_BLUE
};

class Bird
{
public:
    double numberOfCoconuts;
    double voltage;
    double getBaseSpeed()
    {

    }

    double getBaseSpeed(double)
    {

    }

    double getLoadFactor()
    {

    }
    BIRD type;
    double getSpeed()
    {
        switch (type)
        {
            case BIRD::EUROPEAN:
                return getBaseSpeed();
            case BIRD::AFRICAN:
                return getBaseSpeed() - getLoadFactor() * numberOfCoconuts;
            case BIRD::NORWEGIAN_BLUE:
                return  getBaseSpeed(voltage);
        }
        throw std::runtime_error("Should be unreachable");
    }
};
}

namespace after
{
class Bird
{
    public:
    double virtual getSpeed()=0;
    double  getBaseSpeed(){}
    double getBaseSpeed(double){}
};

class European :public Bird
{
    double getSpeed()
    {
        return getBaseSpeed();
    }
};

class African : public Bird
{
public:
    double getLoadFactor(){}
    double numberOfCoconuts;
    double getSpeed()
    {
        return getBaseSpeed() - getLoadFactor() * numberOfCoconuts;
    }
};

class NorwegianBlue:public Bird
{
    public:
    double voltage;
    double getSpeed()
    {
        return getBaseSpeed(voltage);
    }
};

}
int main()
{

/*
    1+2*3

and we want to represent this as tree:

         +
        / \
       1   *
          / \
         2   3

Node
ValueNode
OpNode Multipication, AdditionNode
*/

    {
        using namespace after;
        AdditionNode *Node1=new AdditionNode;
        ValueNode *Node2=new ValueNode;
        Node2->value=1;

        Multipication *Node3=new Multipication;

        Node1->left=Node2;
        Node1->right=Node3;


        ValueNode *Node4=new ValueNode;
        ValueNode *Node5=new ValueNode;

        Node4->value=2;
        Node5->value=3;

        Node3->left=Node4;
        Node3->right=Node5;

        std::cout<< Node1->evaluate()<<std::endl;

        delete Node1,Node2, Node3, Node4, Node5;

    }
    {
        using namespace after;
        Bird *bird=new African;
        double speed = bird->getSpeed();
        delete bird;

    }


}
