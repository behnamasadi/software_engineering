//http://www.vishalchovatiya.com/iterator-design-pattern-in-modern-cpp/
//https://www.robertlarsononline.com/2017/04/24/iterator-pattern-using-cplusplus/
//https://cppcodetips.wordpress.com/2016/08/14/iterator-pattern-using-c/
//https://www.geeksforgeeks.org/iterator-pattern/
class Iterator
{
    public:
    virtual void getNext()=0;
    virtual bool hasMore()=0;

};

class IteratorCollection
{
    virtual Iterator* createIterator()=0;
};

class ConcreteCollection: public IteratorCollection
{

};
int main()
{

}
