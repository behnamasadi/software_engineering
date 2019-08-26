#include <iostream>
#include <vector>
#include <list>


class  IBillingStrategy
{
    public:
    double virtual GetActPrice(double rawPrice){}//{        std::cout<<"IBillingStrategy"<<std::endl;}
};


// Normal billing strategy (unchanged price)
class NormalStrategy : public IBillingStrategy
{
    public:
    double  GetActPrice(double rawPrice) override
    {
        return rawPrice;
    }
};

// Strategy for Happy hour (50% discount)
class HappyHourStrategy : public IBillingStrategy
{
public:
    double  GetActPrice(double rawPrice) override
    {
        return rawPrice * 0.5;
    }
};

class Customer
{
    private:
    std::list<double> drinks;

public:
    IBillingStrategy *Strategy;

public :
    Customer(IBillingStrategy *strategy)
    {

        this->Strategy = strategy;
    }

    void Add(double price, int quantity)
    {
        this->drinks.push_back(this->Strategy->GetActPrice(price * quantity));
    }

    // Payment of bill
    void PrintBill()
    {
        double sum = 0;
        for(auto i : this->drinks)
        {
            sum += i;
        }
        std::cout<<"Total due: " << sum <<std::endl;
    }
};



int main()
{
    // Prepare strategies
    IBillingStrategy *normalStrategy=new NormalStrategy;
    IBillingStrategy *happyHourStrategy=new  HappyHourStrategy;

    Customer firstCustomer =  Customer(normalStrategy);

    // Normal billing
    firstCustomer.Add(1.0, 1);

    // Start Happy Hour
    firstCustomer.Strategy = happyHourStrategy;
    firstCustomer.Add(1.0, 2);

    // New Customer
    Customer secondCustomer =  Customer(happyHourStrategy);
    secondCustomer.Add(0.8, 1);
    // The Customer pays
    firstCustomer.PrintBill();

    // End Happy Hour
    secondCustomer.Strategy = normalStrategy;
    secondCustomer.Add(1.3, 2);
    secondCustomer.Add(2.5, 1);
    secondCustomer.PrintBill();
    delete normalStrategy,happyHourStrategy;
}




