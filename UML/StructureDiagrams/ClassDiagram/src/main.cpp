#include <string>
#include <memory>
#include <vector>
#include <functional>
class Address
{

};
class Person
{
private:
    int id;
    std::string name;
    static int count;
    Address & m_address;
public:
    void setName(std::string name);
    std::string getCenter();
    virtual void calculateSalary();
};



//Composition
class Heart{};
class Human
{
private:
    Heart heart;
public:
    Human(Heart heart) : heart(heart) {}
};


// Association
class Team
{
private:
    std::shared_ptr<Person> leader;
public:
    void setLeader(std::shared_ptr<Person> leader);
};

int main()
{
    std::vector<std::reference_wrapper<Address> > m_Addresses{};
}


/*
https://cppcodetips.wordpress.com/2013/12/23/uml-class-diagram-explained-with-c-samples/
https://stackoverflow.com/questions/31978324/what-exactly-is-stdatomic
https://www.uml-diagrams.org/index-examples.html
https://creately.com/lp/uml-diagram-tool/
https://creately.com/blog/diagrams/uml-diagram-types-examples/#CommDiagram
https://www.visual-paradigm.com/tutorials/
https://www.visual-paradigm.com/guide/uml-unified-modeling-language/uml-class-diagram-tutorial/
https://en.cppreference.com/w/cpp/utility/functional/reference_wrapper

*/
