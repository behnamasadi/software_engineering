#include <vector>
#include <algorithm>    // For std::remove
#include <iostream>     // For printing (optional)

enum class EVENT
{
    USER_LOGGED_IN,
    USER_LOGGED_OFF,
    MESSAGE
};

class Subscriber
{
public:
    // It's more conventional to write 'virtual void update(...) = 0;'
    virtual void update(EVENT e) = 0;
};

class Client : public Subscriber
{
public:
    void update(EVENT e) override
    {
        // Implementation for handling the event.
        // For example:
        std::cout << "Client received event code: " 
                  << static_cast<int>(e) << std::endl;
    }
};

class Server
{
    std::vector<Subscriber*> listOfClients;

public:
    void addSubscriber(Subscriber* s)
    {
        listOfClients.push_back(s);
    }

    void removeSubscriber(Subscriber* s)
    {
        // Simple approach:
        // 1. Use remove to "shift" the pointer out
        // 2. Erase it from the vector
        auto it = std::remove(listOfClients.begin(), listOfClients.end(), s);
        if (it != listOfClients.end())
        {
            listOfClients.erase(it, listOfClients.end());
        }
    }

    void notify(EVENT e)
    {
        for (auto* subscriber : listOfClients)
        {
            subscriber->update(e);
        }
    }
};

int main()
{
    Server server;
    Client client1, client2;

    server.addSubscriber(&client1);
    server.addSubscriber(&client2);

    // Notify all subscribed clients that a user has logged in
    server.notify(EVENT::USER_LOGGED_IN);

    // Optionally remove client2 from notifications
    server.removeSubscriber(&client2);
    
    // Further notify only client1
    server.notify(EVENT::MESSAGE);

    return 0;
}
