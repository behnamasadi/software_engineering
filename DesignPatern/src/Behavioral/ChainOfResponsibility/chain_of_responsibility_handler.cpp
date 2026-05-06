// Chain of Responsibility — conceptual example.
// Each handler tries to process the request; if it can't, it forwards to the
// next handler in the chain. The sender is decoupled from the eventual handler.

#include <iostream>

class Handler {
public:
    virtual ~Handler() = default;

    // Returns *this so chains can be built fluently: a.setNext(&b).setNext(&c);
    Handler& setNext(Handler* next) {
        next_ = next;
        return *next;
    }

    virtual void handle(int request) {
        if (next_) next_->handle(request);
        else std::cout << "No handler for " << request << '\n';
    }

protected:
    Handler* next_ = nullptr;
};

// Each concrete handler claims requests of one residue class mod 4.
class ModHandler : public Handler {
public:
    ModHandler(int id, int residue) : id_(id), residue_(residue) {}

    void handle(int request) override {
        if (request % 4 == residue_) {
            std::cout << "H" << id_ << " handled " << request << '\n';
        } else {
            std::cout << "H" << id_ << " passed " << request << '\n';
            Handler::handle(request);  // forward
        }
    }

private:
    int id_;
    int residue_;
};

int main() {
    ModHandler h1(1, 1), h2(2, 2), h3(3, 3), h0(4, 0);
    h1.setNext(&h2).setNext(&h3).setNext(&h0);

    for (int i = 1; i <= 6; ++i) {
        h1.handle(i);
        std::cout << "---\n";
    }
}
