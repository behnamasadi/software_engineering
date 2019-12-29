#include <string>
#include <iostream>
#include <vector>

class Fruit;
class Book;

class ShoppingCartVisitor
{
public:
    int virtual visit(Book *book){}
    int virtual visit(Fruit *fruit){}
    //int virtual visit(ItemElement *itemElement){}


};

class ItemElement
{
public:
    int virtual accept(ShoppingCartVisitor *visitor){}
};

class Book : public ItemElement
{
private:
    int price;
     std::string isbnNumber;

    public:
     Book(int cost, std::string isbn)
    {
        this->price=cost;
        this->isbnNumber=isbn;
    }

    int getPrice()
    {
        return price;
    }

    std::string getIsbnNumber()
    {
        return isbnNumber;
    }


    int accept(ShoppingCartVisitor* visitor)
    {
        return visitor->visit(this);
    }

};

class Fruit : public ItemElement
{
    int pricePerKg;
    int weight;
    std::string name;

public:
    Fruit(int priceKg, int wt, std::string nm)
    {
        this->pricePerKg=priceKg;
        this->weight=wt;
        this->name = nm;
    }

    int getPricePerKg()
    {
        return pricePerKg;
    }

    int getWeight()
    {
        return weight;
    }

    std::string getName()
    {
        return this->name;
    }


    int accept(ShoppingCartVisitor *visitor)
    {
        return visitor->visit(this);
    }

};

class ShoppingCartVisitorImpl : public ShoppingCartVisitor
{


public: int visit(Book *book)
    {
        int cost=0;
        //apply 5$ discount if book price is greater than 50
        if(book->getPrice() > 50)
        {
            cost = book->getPrice()-5;
        }
        else
            cost = book->getPrice();

        std::cout<<"Book ISBN::"<<book->getIsbnNumber() << " cost ="<<cost<<std::endl;
        return cost;
    }

    int visit(Fruit *fruit)
    {
        int cost = fruit->getPricePerKg()*fruit->getWeight();
        std::cout<<fruit->getName() << " cost = "<<cost<<std::endl;
        return cost;
    }

};

int calculatePrice(std::vector<ItemElement*> &items)
{
    ShoppingCartVisitor *visitor = new ShoppingCartVisitorImpl();
    int sum=0;
    for(ItemElement* item : items)
    {
        sum = sum + item->accept(visitor);
    }
    delete visitor;
    return sum;
}

int main()
{
    std::vector<ItemElement*> items = {new Book(20, "1234"),
                        new Book(100, "5678"), new Fruit(10, 2, "Banana"),
                        new Fruit(5, 5, "Apple")};

    int total = calculatePrice(items);
    std::cout<<"Total Cost = "<<total<<std::endl;
}
