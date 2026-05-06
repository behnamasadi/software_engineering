// Proxy — protection proxy that gates access to a sensitive object.
//
// `SecurePettyCash` actually holds the money. `PettyCashProxy` wraps it and
// only forwards `withdraw()` if the requesting Person is on the authorized
// list. The real object never sees an unauthorized call.

#include <algorithm>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

class Person {
public:
    explicit Person(std::string name) : name_(std::move(name)) {}

    const std::string& name() const { return name_; }

private:
    std::string name_;
};

class SecurePettyCash {
public:
    SecurePettyCash() : balance_(500) {}

    bool withdraw(int amount) {
        if (amount > balance_) {
            std::cout << "  not enough funds (balance=" << balance_ << ")\n";
            return false;
        }
        balance_ -= amount;
        return true;
    }

    int balance() const { return balance_; }

private:
    int balance_;
};

class PettyCashProxy {
public:
    PettyCashProxy() : cash_(std::make_unique<SecurePettyCash>()) {}

    bool withdraw(const Person& person, int amount) {
        static const std::vector<std::string> authorized = {"Tom", "Harry", "Bubba"};

        auto it = std::find(authorized.begin(), authorized.end(), person.name());
        if (it == authorized.end()) {
            std::cout << "  access denied for " << person.name() << '\n';
            return false;
        }
        return cash_->withdraw(amount);
    }

    int balance() const { return cash_->balance(); }

private:
    std::unique_ptr<SecurePettyCash> cash_;
};

int main() {
    PettyCashProxy pc;
    std::vector<Person> workers = {Person("Tom"), Person("Dick"),
                                   Person("Harry"), Person("Bubba")};

    int amount = 100;
    for (const auto& w : workers) {
        if (pc.withdraw(w, amount))
            std::cout << "  $" << amount << " withdrawn by " << w.name() << '\n';
        else
            std::cout << "  no money for " << w.name() << '\n';
        amount += 100;
    }

    std::cout << "Remaining balance: $" << pc.balance() << '\n';
}
