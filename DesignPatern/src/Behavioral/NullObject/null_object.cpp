//https://www.codeproject.com/Articles/1042674/NULL-Object-Design-Pattern

// Object Design Pattern


#include <iostream>
#include <string>
#include <vector>
class Emp
{
    protected:
        std::string name;
    public: virtual bool isNull(){}
        std::string virtual  getName(){}
};

class Coder : public Emp
{
    public:
        Coder(std::string name)
        {
            this->name = name;
        }

    public: std::string getName()
        {
            return name;
        }

    bool isNull()
        {
            return false;
        }
};

class NoClient : public Emp
{
public:
    std::string getName()
    {
        return "Not Available";
    }


    bool isNull()
    {
        return true;
    }
};

class EmpData
{
public:
    static std::vector<std::string> names;
    static Emp* getClient(std::string name)
    {
        for (int i = 0; i < names.size(); i++)
        {
            if (names[i].compare(name) ==0)
            {
                return new Coder(name);
            }
        }
        return new NoClient();
    }
};

std::vector<std::string> EmpData::names {"Lokesh", "Kushagra", "Vikram"};


int main()
{
        Emp *emp1 = EmpData::getClient("Lokesh");
        Emp *emp2 = EmpData::getClient("Kushagra");
        Emp *emp3 = EmpData::getClient("Vikram");
        Emp *emp4 = EmpData::getClient("Rishabh");


        std::cout<<emp1->getName()<<std::endl;
        std::cout<<emp2->getName()<<std::endl;
        std::cout<<emp3->getName()<<std::endl;
        std::cout<<emp4->getName()<<std::endl;
}

