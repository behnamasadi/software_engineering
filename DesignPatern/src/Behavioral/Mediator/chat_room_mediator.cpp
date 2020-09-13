#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
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


/*
//ref: http://www.vishalchovatiya.com/mediator-design-pattern-in-modern-cpp/

struct ChatRoom
{
    virtual void broadcast(std::string from, std::string msg) = 0;
    virtual void message(std::string from, std::string to, std::string msg) = 0;
};

struct Person {
    std::string              m_name;
    ChatRoom*           m_room{nullptr};
    std::vector<std::string>      m_chat_log;

    Person(std::string n) : m_name(n) {}

    void say(std::string msg) const { m_room->broadcast(m_name, msg); }
    void pm(std::string to, std::string msg) const { m_room->message(m_name, to, msg); }
    void receive(std::string from, std::string msg) {
        std::string s{from + ": \"" + msg + "\""};
        std::cout << "[" << m_name << "'s chat session]" << s << "\n";
        m_chat_log.emplace_back(s);
    }
};

struct GoogleChat : ChatRoom
{
    std::vector<Person*>     m_people;

    void broadcast(std::string from, std::string msg) {
        for (auto p : m_people)
            if (p->m_name != from)
                p->receive(from, msg);
    }

    void join(Person *p) {
        std::string join_msg = p->m_name + " joins the chat";
        broadcast("room", join_msg);
        p->m_room = this;
        m_people.push_back(p);
    }

    void message(std::string from, std::string to, std::string msg) {
        auto target = std::find_if(begin(m_people), end(m_people),
        [&](const Person *p) {
            return p->m_name == to;
        });

        if (target != end(m_people)) (*target)->receive(from, msg);
    }
};

int main() {
    GoogleChat room;

    Person john{"John"};
    Person jane{"Jane"};
    room.join(&john);
    room.join(&jane);
    john.say("hi room");
    jane.say("oh, hey john");

    Person simon{"Simon"};
    room.join(&simon);
    simon.say("hi everyone!");

    jane.pm("Simon", "glad you found us, simon!");

    return EXIT_SUCCESS;
}
*/




#include <iostream>
#include <string>
#include <list>

class MediatorInterface;

class ColleagueInterface {
        std::string name;
    public:
        ColleagueInterface (const std::string& newName) : name (newName) {}
        std::string getName() const {return name;}
        virtual void sendMessage (const MediatorInterface&, const std::string&) const = 0;
        virtual void receiveMessage (const ColleagueInterface*, const std::string&) const = 0;
};

class Colleague : public ColleagueInterface {
    public:
        using ColleagueInterface::ColleagueInterface;
        virtual void sendMessage (const MediatorInterface&, const std::string&) const override;
    private:
        virtual void receiveMessage (const ColleagueInterface*, const std::string&) const override;
};

class MediatorInterface {
    private:
        std::list<ColleagueInterface*> colleagueList;
    public:
        const std::list<ColleagueInterface*>& getColleagueList() const {return colleagueList;}
        virtual void distributeMessage (const ColleagueInterface*, const std::string&) const = 0;
        virtual void registerColleague (ColleagueInterface* colleague) {colleagueList.emplace_back (colleague);}
};

class Mediator : public MediatorInterface {
    virtual void distributeMessage (const ColleagueInterface*, const std::string&) const override;
};

void Colleague::sendMessage (const MediatorInterface& mediator, const std::string& message) const {
    mediator.distributeMessage (this, message);
}

void Colleague::receiveMessage (const ColleagueInterface* sender, const std::string& message) const {
    std::cout << getName() << " received the message from " << sender->getName() << ": " << message << std::endl;
}

void Mediator::distributeMessage (const ColleagueInterface* sender, const std::string& message) const {
    for (const ColleagueInterface* x : getColleagueList())
        if (x != sender)  // Do not send the message back to the sender
            x->receiveMessage (sender, message);
}

int main() {
    Colleague *bob = new Colleague ("Bob"),  *sam = new Colleague ("Sam"),  *frank = new Colleague ("Frank"),  *tom = new Colleague ("Tom");
    Colleague* staff[] = {bob, sam, frank, tom};
    Mediator mediatorStaff, mediatorSamsBuddies;
    for (Colleague* x : staff)
        mediatorStaff.registerColleague(x);
    bob->sendMessage (mediatorStaff, "I'm quitting this job!");
    mediatorSamsBuddies.registerColleague (frank);  mediatorSamsBuddies.registerColleague (tom);  // Sam's buddies only
    sam->sendMessage (mediatorSamsBuddies, "Hooray!  He's gone!  Let's go for a drink, guys!");
    return 0;
}
