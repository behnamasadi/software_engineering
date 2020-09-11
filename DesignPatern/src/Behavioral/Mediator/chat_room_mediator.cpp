#include <string>
#include <iostream>
//http://www.vishalchovatiya.com/mediator-design-pattern-in-modern-cpp/
/*
public delegate void MessageReceivedEventHandler(string message, string from);

public class Mediator
{
    public event MessageReceivedEventHandler MessageReceived;

    public void Send(string message, string from)
    {
        if (MessageReceived != null)
        {
            Console.WriteLine("Sending '{0}' from {1}", message, from);
            MessageReceived(message, from);
        }
    }
}

public class Person
{
    private:
    Mediator m_mediator;
    std::string m_Name;

public:

    std::string getName(){return m_Name;}
    setName(std::string name){m_Name(name);}


    void Receive(std::string message, std::string from)
    {
        if (from != Name)
            std::cout << Name<<"received "<< message<< " from:" <<from<<std::endl;
    }



    public Person(Mediator mediator, string name)
    {
        Name = name;
        m_mediator = mediator;
        m_mediator.MessageReceived += new MessageReceivedEventHandler(Receive);
    }


    public void Send(string message)
    {
        m_mediator.Send(message, Name);
    }
}
*/

int main()
{

}
