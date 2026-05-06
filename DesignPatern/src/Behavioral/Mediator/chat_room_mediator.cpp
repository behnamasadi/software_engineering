// Mediator — chat room.
// Users don't keep references to each other; they post to the room and the
// room fans the message out. Adding/removing users doesn't ripple through
// every other user's code.

#include <iostream>
#include <string>
#include <vector>

class User;

class ChatRoom {
public:
    void join(User& user) { users_.push_back(&user); }
    void broadcast(const User& sender, const std::string& message);

private:
    std::vector<User*> users_;
};

class User {
public:
    User(std::string name, ChatRoom& room) : name_(std::move(name)), room_(room) {
        room_.join(*this);
    }

    const std::string& name() const { return name_; }

    void send(const std::string& message) const {
        std::cout << "[" << name_ << "] -> " << message << '\n';
        room_.broadcast(*this, message);
    }

    void receive(const User& from, const std::string& message) const {
        std::cout << "  " << name_ << " heard from " << from.name() << ": " << message << '\n';
    }

private:
    std::string name_;
    ChatRoom& room_;
};

void ChatRoom::broadcast(const User& sender, const std::string& message) {
    for (User* u : users_) {
        if (u != &sender) u->receive(sender, message);
    }
}

int main() {
    ChatRoom staff;
    User bob("Bob", staff), sam("Sam", staff), frank("Frank", staff);

    bob.send("I'm quitting this job!");
    sam.send("Anyone want coffee?");
}
