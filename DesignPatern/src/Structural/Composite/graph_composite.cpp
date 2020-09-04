//http://www.vishalchovatiya.com/composite-design-pattern-in-modern-cpp/
#include <iostream>
#include <string>
#include <vector>

class Shape
{
protected:
    std::string m_name;
public:
    Shape(std::string name=""):m_name(name){}

    void virtual draw()=0;
};

class Circle: public Shape
{

public:
    Circle(std::string name):Shape(name){}
    void draw()override
    {
        std::cout<<"drawing circle name:"<<m_name <<std::endl;
    }
};


class Rectangle: public Shape
{

public:
    Rectangle(std::string name):Shape(name){}
    void draw()override
    {
        std::cout<<"drawing rectangle name:"<<m_name <<std::endl;
    }
};


class Group: public Shape
{
    std::vector<Shape*> m_objects;
public:
    Group(std::string name):Shape(name){}
    void draw()
    {
        std::cout<<"drawing "<<m_name <<std::endl;
        for(std::vector<Shape*>::iterator it=m_objects.begin();it!=m_objects.end();it++)
        {
             (*it)->draw();
        }
    }

    void add(Shape* m_object)
    {
        m_objects.push_back(m_object);
    }
};

int main()
{



    Shape *circle1=new Circle("circle1");
    Group *subgroup=new Group("subgroup1");
    subgroup->add(circle1);

    Shape *circle2=new Circle("circle2");
    Shape *circle3=new Circle("circle3");

    Group *root=new Group("root");
    root->add(circle2);
    root->add(circle3);
    root->add(subgroup);
    root->draw();

}
