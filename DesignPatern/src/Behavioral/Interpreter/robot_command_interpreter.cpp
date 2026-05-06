// Interpreter — robot command DSL.
// A tiny grammar: "MOVE <dir> <n>" | "TURN <dir> <deg>"
// Parser turns a string into a Command object; interpret() executes it.

#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

class Command {
public:
    virtual ~Command() = default;
    virtual void interpret() const = 0;
};

class MoveCommand : public Command {
public:
    MoveCommand(std::string direction, int distance)
        : direction_(std::move(direction)), distance_(distance) {}
    void interpret() const override {
        std::cout << "Move " << direction_ << " " << distance_ << " units\n";
    }
private:
    std::string direction_;
    int distance_;
};

class TurnCommand : public Command {
public:
    TurnCommand(std::string direction, int degrees)
        : direction_(std::move(direction)), degrees_(degrees) {}
    void interpret() const override {
        std::cout << "Turn " << direction_ << " " << degrees_ << " degrees\n";
    }
private:
    std::string direction_;
    int degrees_;
};

std::unique_ptr<Command> parse(const std::string& line) {
    std::istringstream iss(line);
    std::string action, direction;
    int value;
    iss >> action >> direction >> value;

    if (action == "MOVE") return std::make_unique<MoveCommand>(direction, value);
    if (action == "TURN") return std::make_unique<TurnCommand>(direction, value);
    return nullptr;
}

int main() {
    std::vector<std::string> program = {
        "MOVE FORWARD 10",
        "TURN LEFT 90",
        "MOVE BACKWARD 5",
        "DANCE WILDLY 1",  // unknown
    };

    for (const auto& line : program) {
        if (auto cmd = parse(line)) cmd->interpret();
        else std::cout << "Invalid: " << line << '\n';
    }
}
