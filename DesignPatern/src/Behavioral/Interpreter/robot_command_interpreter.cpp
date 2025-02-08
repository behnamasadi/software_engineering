#include <iostream>
#include <vector>
#include <memory>
#include <sstream>

// Abstract Expression (Command)
class Command {
public:
    virtual void interpret() const = 0;
    virtual ~Command() = default;
};

// Terminal Expression: Move Command
class MoveCommand : public Command {
    std::string direction;
    int distance;
public:
    MoveCommand(std::string dir, int dist) : direction(std::move(dir)), distance(dist) {}

    void interpret() const override {
        std::cout << "Moving " << direction << " by " << distance << " units.\n";
    }
};

// Terminal Expression: Turn Command
class TurnCommand : public Command {
    std::string direction;
    int angle;
public:
    TurnCommand(std::string dir, int ang) : direction(std::move(dir)), angle(ang) {}

    void interpret() const override {
        std::cout << "Turning " << direction << " by " << angle << " degrees.\n";
    }
};

// Parser (Converts strings into command objects)
class CommandParser {
public:
    static std::shared_ptr<Command> parse(const std::string& input) {
        std::istringstream iss(input);
        std::string action, direction;
        int value;
        iss >> action >> direction >> value;

        if (action == "MOVE") {
            return std::make_shared<MoveCommand>(direction, value);
        } else if (action == "TURN") {
            return std::make_shared<TurnCommand>(direction, value);
        }
        return nullptr;
    }
};

// Main execution
int main() {
    std::vector<std::string> commands = {
        "MOVE FORWARD 10",
        "TURN LEFT 90",
        "MOVE BACKWARD 5"
    };

    for (const auto& cmd : commands) {
        auto commandObj = CommandParser::parse(cmd);
        if (commandObj) {
            commandObj->interpret();
        } else {
            std::cout << "Invalid command: " << cmd << std::endl;
        }
    }
    return 0;
}

