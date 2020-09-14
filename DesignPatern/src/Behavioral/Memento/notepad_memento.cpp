#include <iostream>
#include <string>
#include <memory>
#include <ctime>
#include <stack>

class Memento
{
public:
    virtual std::string state()=0;
    virtual std::string date()=0;
    virtual std::string getName()=0;
};

class ConcreteMemento: public Memento
{
private:
    std::string m_state;
    std::string m_date;
public:
    ConcreteMemento(std::string state)
    {
        this->m_state=state;
        std::time_t now =std::time(0);
        this->m_date = std::ctime(&now);
    }


    std::string state() override
    {
        return this->m_state;
    }

    std::string date() override
    {
        return this->m_date;
    }
    std::string getName() override
    {
        return this->m_date + " / " + this->m_state;
    }


};

class Originator
{
    std::string m_state;
public:
    Originator(std::string state) : m_state(state) {
        std::cout << "Originator: My initial state is: " << this->m_state << "\n";
      }

    Memento *Save()
    {
        return new ConcreteMemento(this->m_state);
    }
    void Restore(Memento* memento)
    {
        this->m_state=memento->state();
        std::cout << "Originator: My state has changed to: " << this->m_state << "\n";
    }

    void changeText(std::string text)
    {
        this->m_state = text;
        std::cout << "Originator: My state has changed to: " << this->m_state << "\n";

    }
};

class CareTaker
{
    std::stack<Memento*> m_mementos;
    Originator *m_originator;

public:
    CareTaker(Originator *originator)
    {
         this->m_originator=originator;
    }

    void backUp()
    {
        this->m_mementos.push(this->m_originator->Save());
    }

    void undo()
    {
       Memento* memento= m_mementos.top();
       m_mementos.pop();
       std::cout << "Caretaker: Restoring state to: " << memento->getName() << "\n";
       this->m_originator->Restore(memento);
    }
};



int main()
{
    Originator* originator=new Originator("intial state");
    CareTaker *caretaker = new CareTaker(originator);

    originator->changeText("mumbo");
    caretaker ->backUp();

    originator->changeText("jumbo");
    caretaker ->backUp();

    caretaker->undo();

    originator->changeText("dumbo");
    caretaker ->backUp();


    caretaker->undo();
    caretaker->undo();

}
