// Chain of Responsibility — ATM cash dispenser.
// Each dispenser handles its denomination, then forwards the remainder.

#include <iostream>

class Dispenser {
public:
    Dispenser(int denomination) : denomination_(denomination) {}
    virtual ~Dispenser() = default;

    void setNext(Dispenser* next) { next_ = next; }

    void dispense(int amount) {
        int count = amount / denomination_;
        if (count > 0) {
            std::cout << "Dispensing " << count << " x $" << denomination_ << '\n';
            amount %= denomination_;
        }
        if (amount > 0 && next_) next_->dispense(amount);
        else if (amount > 0) std::cout << "Cannot dispense remaining $" << amount << '\n';
    }

private:
    int denomination_;
    Dispenser* next_ = nullptr;
};

int main() {
    Dispenser hundred(100), fifty(50), twenty(20), ten(10), five(5), one(1);
    hundred.setNext(&fifty);
    fifty.setNext(&twenty);
    twenty.setNext(&ten);
    ten.setNext(&five);
    five.setNext(&one);

    int amount = 187;
    std::cout << "Withdrawing $" << amount << "\n";
    hundred.dispense(amount);
}
