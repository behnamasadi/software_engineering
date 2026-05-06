// Decorator — wrap a Logger to add extra sinks. The base FileLogger logs to a
// file; SQLLogger and HTMLLogger each wrap a logger, forward the message,
// and then write to their own sink. Stack them in any order to log to many
// places at once.

#include <iostream>
#include <memory>
#include <string>
#include <utility>

class Logger {
public:
    virtual ~Logger() = default;
    virtual void log(const std::string& event) const = 0;
    virtual std::string description() const = 0;
};

class FileLogger : public Logger {
public:
    void log(const std::string& event) const override {
        std::cout << event << " -> file\n";
    }
    std::string description() const override { return "File Logger"; }
};

// Base decorator.
class EnhancedLogger : public Logger {
public:
    explicit EnhancedLogger(std::unique_ptr<Logger> inner)
        : inner_(std::move(inner)) {}

protected:
    std::unique_ptr<Logger> inner_;
};

class SQLLogger : public EnhancedLogger {
public:
    using EnhancedLogger::EnhancedLogger;

    void log(const std::string& event) const override {
        inner_->log(event);
        std::cout << event << " -> SQL database\n";
    }
    std::string description() const override {
        return inner_->description() + " + SQL Logger";
    }
};

class HTMLLogger : public EnhancedLogger {
public:
    using EnhancedLogger::EnhancedLogger;

    void log(const std::string& event) const override {
        inner_->log(event);
        std::cout << event << " -> HTML file\n";
    }
    std::string description() const override {
        return inner_->description() + " + HTML Logger";
    }
};

int main() {
    std::unique_ptr<Logger> logger = std::make_unique<FileLogger>();
    logger = std::make_unique<SQLLogger>(std::move(logger));
    logger = std::make_unique<HTMLLogger>(std::move(logger));

    std::cout << logger->description() << '\n';
    logger->log("User login event");
}
