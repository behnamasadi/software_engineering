#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>  // ✅ Added for std::find

using namespace std;

class Person
{
    string nameString;
    static vector<string> nameList;
    static int next;

public:
    Person()
    {
        if (next < nameList.size())
            nameString = nameList[next++];
        else
            nameString = "Unknown";
    }

    string getName() const
    {
        return nameString;
    }
};

// Initialize static name list
vector<string> Person::nameList = {"Tom", "Dick", "Harry", "Bubba"};
int Person::next = 0;

// Secure class handling actual cash transactions
class SecurePettyCash
{
private:
    int balance;

public:
    SecurePettyCash() : balance(500) {}

    bool withdraw(int amount)
    {
        if (amount > balance)
        {
            cout << "❌ Not enough funds in petty cash.\n";
            return false;
        }
        balance -= amount;
        return true;
    }

    int getBalance() const
    {
        return balance;
    }
};

// Proxy class controlling access to SecurePettyCash
class PettyCashProxy
{
private:
    unique_ptr<SecurePettyCash> realPettyCash;

public:
    PettyCashProxy() : realPettyCash(make_unique<SecurePettyCash>()) {}

    bool withdraw(const Person& person, int amount)
    {
        static vector<string> authorizedUsers = {"Tom", "Harry", "Bubba"};

        // ✅ Fixed std::find issue
        if (std::find(authorizedUsers.begin(), authorizedUsers.end(), person.getName()) != authorizedUsers.end())
        {
            return realPettyCash->withdraw(amount);
        }
        else
        {
            cout << "⛔ Access denied for " << person.getName() << ".\n";
            return false;
        }
    }

    int getBalance() const
    {
        return realPettyCash->getBalance();
    }
};

int main()
{
    PettyCashProxy pc;
    vector<unique_ptr<Person>> workers;
    
    // Creating 4 workers
    for (int i = 0; i < 4; i++)
        workers.push_back(make_unique<Person>());

    int amount = 100;
    for (const auto& worker : workers)
    {
        if (!pc.withdraw(*worker, amount))
            cout << "❌ No money for " << worker->getName() << ".\n";
        else
            cout << "✅ " << amount << " dollars withdrawn by " << worker->getName() << ".\n";

        amount += 100;
    }

    cout << "\n💰 Remaining balance in petty cash: $" << pc.getBalance() << '\n';

    return 0;
}
