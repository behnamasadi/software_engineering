#include <iostream>
#include <vector>
#include <memory>

using namespace std;

namespace before
{
    class Stooge
    {
      public:
        virtual void performAction() = 0;
        virtual ~Stooge() = default;
    };

    class Larry : public Stooge
    {
      public:
        void performAction() override
        {
            cout << "Larry: poke eyes\n";
        }
    };
    
    class Moe : public Stooge
    {
      public:
        void performAction() override
        {
            cout << "Moe: slap head\n";
        }
    };
    
    class Curly : public Stooge
    {
      public:
        void performAction() override
        {
            cout << "Curly: suffer abuse\n";
        }
    };
}

namespace after
{
    class Stooge
    {
      public:
        // Factory Method using smart pointers
        static unique_ptr<Stooge> createStooge(int choice);
        virtual void performAction() = 0;
        virtual ~Stooge() = default;
    };

    class Larry : public Stooge
    {
      public:
        void performAction() override
        {
            cout << "Larry: poke eyes\n";
        }
    };

    class Moe : public Stooge
    {
      public:
        void performAction() override
        {
            cout << "Moe: slap head\n";
        }
    };

    class Curly : public Stooge
    {
      public:
        void performAction() override
        {
            cout << "Curly: suffer abuse\n";
        }
    };

    unique_ptr<Stooge> Stooge::createStooge(int choice)
    {
        if (choice == 1)
            return make_unique<Larry>();
        else if (choice == 2)
            return make_unique<Moe>();
        else
            return make_unique<Curly>();
    }
}

int main()
{
    {
        cout << "\n🔴 BEFORE: Hardcoded Stooge Creation\n";
        vector<unique_ptr<before::Stooge>> stooges;
        int choice;

        while (true)
        {
            cout << "Larry(1) Moe(2) Curly(3) Go(0): ";
            cin >> choice;
            if (choice == 0)
                break;
            else if (choice == 1)
                stooges.push_back(make_unique<before::Larry>());
            else if (choice == 2)
                stooges.push_back(make_unique<before::Moe>());
            else
                stooges.push_back(make_unique<before::Curly>());
        }

        for (const auto& stooge : stooges)
            stooge->performAction();
    }

    {
        cout << "\n🟢 AFTER: Factory Method with Smart Pointers\n";
        vector<unique_ptr<after::Stooge>> stooges;
        int choice;

        while (true)
        {
            cout << "Larry(1) Moe(2) Curly(3) Go(0): ";
            cin >> choice;
            if (choice == 0)
                break;
            stooges.push_back(after::Stooge::createStooge(choice));
        }

        for (const auto& stooge : stooges)
            stooge->performAction();
    }

    return 0;
}
