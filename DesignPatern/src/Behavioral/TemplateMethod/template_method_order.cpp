//ref: https://www.geeksforgeeks.org/template-method-design-pattern/
#include <iostream>

class OrderProcessTemplate
{
public:
    bool isGift;
    void virtual doSelect()=0;
    void virtual doPayment()=0;
    void virtual doDelivery()=0;

    void giftWrap()
    {
       std::cout<< "Gift wrap successfull"<<std::endl;
    }

    void processOrder(bool isGift)
    {
        doSelect();
        doPayment();
        if (isGift)
        {
            giftWrap();
        }
        doDelivery();
    }
};


class NetOrder: public OrderProcessTemplate
{
public:
    void doSelect() override
    {
        std::cout<< "Item added to online shopping cart"<<std::endl;
        std::cout<< "Get gift wrap preference"<<std::endl;
        std::cout<< "Get delivery address."<<std::endl;
    }

    void doPayment() override
    {
        std::cout<< "Online Payment through Netbanking, card or Paytm"<<std::endl;
    }

    void doDelivery() override
    {
        std::cout<<"Ship the item through post to delivery address"<<std::endl;
    }

};

class StoreOrder :public OrderProcessTemplate
{
public :
    void doSelect()override
    {
         std::cout<<"Customer chooses the item from shelf."<<std::endl;
    }

    void doPayment() override
    {
        std::cout<<"Pays at counter through cash/POS"<<std::endl;
    }

    void doDelivery() override
    {
        std::cout<<"Item deliverd to in delivery counter."<<std::endl;
    }
};



int main()
{
    std::cout<<"Online Order" <<std::endl;
    OrderProcessTemplate* netOrder = new NetOrder();
    netOrder->processOrder(true);


    std::cout<<"Store Order" <<std::endl;
    OrderProcessTemplate *storeOrder = new StoreOrder();
    storeOrder->processOrder(true);
}
