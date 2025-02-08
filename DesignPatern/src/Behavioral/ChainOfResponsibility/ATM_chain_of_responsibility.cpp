#include <iostream>

class CashDispenser
{
protected:
    CashDispenser* next; // Pointer to the next handler in the chain

public:
    CashDispenser() : next(nullptr) {}

    virtual ~CashDispenser() = default;

    void setNext(CashDispenser* nextHandler)
    {
        next = nextHandler;
    }

    void dispense(int amount)
    {
        if (amount > 0)
        {
            dispenseCash(amount);
            if (next != nullptr)
                next->dispense(amount);
        }
    }

    virtual void dispenseCash(int& amount) = 0; // Pure virtual function
};

class HundredDispenser : public CashDispenser
{
public:
    void dispenseCash(int& amount) override
    {
        if (amount >= 100)
        {
            int num = amount / 100;
            amount %= 100;
            std::cout << "Dispensing " << num << " x $100 bills\n";
        }
    }
};

class FiftyDispenser : public CashDispenser
{
public:
    void dispenseCash(int& amount) override
    {
        if (amount >= 50)
        {
            int num = amount / 50;
            amount %= 50;
            std::cout << "Dispensing " << num << " x $50 bills\n";
        }
    }
};

class TwentyDispenser : public CashDispenser
{
public:
    void dispenseCash(int& amount) override
    {
        if (amount >= 20)
        {
            int num = amount / 20;
            amount %= 20;
            std::cout << "Dispensing " << num << " x $20 bills\n";
        }
    }
};

class TenDispenser : public CashDispenser
{
public:
    void dispenseCash(int& amount) override
    {
        if (amount >= 10)
        {
            int num = amount / 10;
            amount %= 10;
            std::cout << "Dispensing " << num << " x $10 bills\n";
        }
    }
};

class FiveDispenser : public CashDispenser
{
public:
    void dispenseCash(int& amount) override
    {
        if (amount >= 5)
        {
            int num = amount / 5;
            amount %= 5;
            std::cout << "Dispensing " << num << " x $5 bills\n";
        }
    }
};

class OneDispenser : public CashDispenser
{
public:
    void dispenseCash(int& amount) override
    {
        if (amount >= 1)
        {
            int num = amount / 1;
            amount %= 1;
            std::cout << "Dispensing " << num << " x $1 bills\n";
        }
    }
};

int main()
{
    int amount;
    std::cout << "Enter withdrawal amount: ";
    std::cin >> amount;

    if (amount <= 0)
    {
        std::cout << "Invalid amount!\n";
        return 1;
    }

    // Creating the chain of handlers
    HundredDispenser hundred;
    FiftyDispenser fifty;
    TwentyDispenser twenty;
    TenDispenser ten;
    FiveDispenser five;
    OneDispenser one;

    // Setting up the chain
    hundred.setNext(&fifty);
    fifty.setNext(&twenty);
    twenty.setNext(&ten);
    ten.setNext(&five);
    five.setNext(&one);

    // Start processing the withdrawal request
    hundred.dispense(amount);

    return 0;
}
