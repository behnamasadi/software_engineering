#include <vector>

enum class EVENT
{
    USER_LOGGED_IN,USER_LOGGED_OFF,MESSAGE
};

class Subscriber
{
public:
    void virtual update(EVENT e)=0;

};


class Client: public Subscriber
{
public:
    void  update(EVENT e) override {}
};

class Server
{
    std::vector< Subscriber *> listOfClients;
public:
    void addSubscriber(){}
    void removeSubscriber(){}

    void notify(EVENT e)
    {
        for(std::size_t i=0;i<listOfClients.size();i++)
        {
            listOfClients[i]->update(e);
        }
    }
};
int main(){}
