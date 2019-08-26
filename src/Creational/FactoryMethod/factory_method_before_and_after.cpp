#include <iostream>
#include <vector>
using namespace std;

namespace before
{
    class Stooge
    {
      public:
        virtual void slap_stick() = 0;
    };

    class Larry: public Stooge
    {
      public:
        void slap_stick()
        {
            cout << "Larry: poke eyes\n";
        }
    };
    class Moe: public Stooge
    {
      public:
        void slap_stick()
        {
            cout << "Moe: slap head\n";
        }
    };
    class Curly: public Stooge
    {
      public:
        void slap_stick()
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
    // Factory Method
    static Stooge *make_stooge(int choice);
    virtual void slap_stick() = 0;
};





class Larry: public Stooge
{
  public:
    void slap_stick()
    {
        cout << "Larry: poke eyes\n";
    }
};
class Moe: public Stooge
{
  public:
    void slap_stick()
    {
        cout << "Moe: slap head\n";
    }
};
class Curly: public Stooge
{
  public:
    void slap_stick()
    {
        cout << "Curly: suffer abuse\n";
    }
};

Stooge *Stooge::make_stooge(int choice)
{
  if (choice == 1)
    return new Larry;
  else if (choice == 2)
    return new Moe;
  else
    return new Curly;
}

}


int main()
{
    {
        vector<before::Stooge*> roles;
        int choice;

        while (true)
        {
            cout << "Larry(1) Moe(2) Curly(3) Go(0): ";
            cin >> choice;
            if (choice == 0)
                break;
            else if (choice == 1)
                roles.push_back(new before::Larry);
            else if (choice == 2)
                roles.push_back(new before::Moe);
            else
                roles.push_back(new before::Curly);
        }
        for (int i = 0; i < roles.size(); i++)
            roles[i]->slap_stick();
        for (int i = 0; i < roles.size(); i++)
            delete roles[i];

    }

    {

        vector<after::Stooge*> roles;
        int choice;
        while (true)
        {
            cout << "Larry(1) Moe(2) Curly(3) Go(0): ";
            cin >> choice;
            if (choice == 0)
                break;
            roles.push_back(after::Stooge::make_stooge(choice));
        }
        for (int i = 0; i < roles.size(); i++)
            roles[i]->slap_stick();
        for (int i = 0; i < roles.size(); i++)
            delete roles[i];
    }

}
