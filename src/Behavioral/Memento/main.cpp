#include <iostream>
#include <string>
#include <memory>
#include <stack>

class memento
{
    std::string text;
public:

    memento(std::string text):text(text){}

    std::string getText()
    {
        return text;
    }
};

class notepad
{
    std::string text;
public:
    std::shared_ptr<memento> setText(std::string text)
    {
        std::shared_ptr<memento> me(new memento(text));
        this->text=text;
        return me;
    }

    std::string getText()
    {
        return text;
    }

    void Undo(std::shared_ptr<memento> previousState)
    {
        text=previousState->getText();
    }
};

class careTaker
{

};


int main()
{
    std::stack<std::shared_ptr<memento>> listOfUndos;
    notepad myWordPreocessor;
    std::shared_ptr<memento> undo_ptr;
    undo_ptr=myWordPreocessor.setText("First");
    listOfUndos.push(undo_ptr);

    undo_ptr=myWordPreocessor.setText("Text Changed");
    listOfUndos.push(undo_ptr);

    std::cout<<listOfUndos.top()->getText() <<std::endl;
    listOfUndos.pop();
    std::cout<<listOfUndos.top()->getText() <<std::endl;


}
