#include <iostream>
#include <string>
#include <vector>
#include <memory>

//size of a tree is the number of nodes

class Node
{
public:
    Node* left, *right;
    Node(int value)
    {
        this->left=nullptr;
        this->right=nullptr;
        this->value=value;
    }
    int value;
};

int treeSizeAfter(std::nullptr_t)
{
    std::cout<<"Passed a null pointer" <<std::endl;
    return 0;
}

int treeSizeAfter(Node *node)
{
    return 1+treeSizeAfter(node->left)+treeSizeAfter(node->right);
}

//int main()
//{

///*

//                    9
//                  /   \
//                8       6
//              /  \        \
//             7    4        2
//*/

//    Node * n9, * n8,* n7,* n4,* n6,* n2;

//    std::cout<<treeSizeAfter(n9) <<std::endl;

//    n9=new Node(9);
//    n8=new Node(8);
//    n7=new Node(7);
//    n4=new Node(4);
//    n6=new Node(6);
//    n2=new Node(2);

//    n9->left=n8;
//    n9->right=n6;

//    n9->left=n7;
//    n9->right=n4;

//    n6->right=n2;

//    std::cout<<treeSizeAfter(n9) <<std::endl;
//}

int main()
{
}
