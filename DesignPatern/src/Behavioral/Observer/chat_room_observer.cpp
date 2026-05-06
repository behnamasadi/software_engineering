// Observer — push model with an event payload.
// Subject pushes an event value into update(); subscribers don't read state
// back from the subject. Cheaper for simple event streams.

#include <algorithm>
#include <iostream>
#include <vector>

enum class Event { UserLoggedIn, UserLoggedOff, Message };

const char* describe(Event e) {
    switch (e) {
        case Event::UserLoggedIn:  return "user-logged-in";
        case Event::UserLoggedOff: return "user-logged-off";
        case Event::Message:       return "message";
    }
    return "?";
}

class Subscriber {
public:
    virtual ~Subscriber() = default;
    virtual void update(Event e) = 0;
};

class Server {
public:
    void subscribe(Subscriber& s)   { subs_.push_back(&s); }
    void unsubscribe(Subscriber& s) {
        subs_.erase(std::remove(subs_.begin(), subs_.end(), &s), subs_.end());
    }

    void publish(Event e) { for (auto* s : subs_) s->update(e); }

private:
    std::vector<Subscriber*> subs_;
};

class Client : public Subscriber {
public:
    explicit Client(const char* name) : name_(name) {}
    void update(Event e) override {
        std::cout << name_ << " got " << describe(e) << '\n';
    }
private:
    const char* name_;
};

int main() {
    Server server;
    Client alice("alice"), bob("bob");

    server.subscribe(alice);
    server.subscribe(bob);

    server.publish(Event::UserLoggedIn);
    server.unsubscribe(bob);
    server.publish(Event::Message);
}
