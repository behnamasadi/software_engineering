#include <iostream>
#include <string>
#include <memory>

// Base Logger class
class Logger
{
protected:
    std::string m_description;

public:
    Logger() : m_description("Unknown Logger") {}

    virtual void log(const std::string& event) const
    {
        std::cout << event << " logged" << std::endl;
    }

    virtual std::string getDescription() const
    {
        return m_description;
    }

    virtual ~Logger() = default; // Ensure proper polymorphic destruction
};

// Concrete File Logger
class FileLogger : public Logger
{
public:
    FileLogger()
    {
        m_description = "File Logger";
    }

    void log(const std::string& event) const override
    {
        std::cout << event << " logged into file" << std::endl;
    }
};

// Abstract Decorator Class
class EnhancedLogger : public Logger
{
protected:
    std::unique_ptr<Logger> m_logger;

public:
    explicit EnhancedLogger(std::unique_ptr<Logger> logger)
        : m_logger(std::move(logger)) {}

    virtual std::string getDescription() const override = 0;
    virtual void log(const std::string& event) const override = 0;
};

// Concrete Decorator - SQL Logger
class SQLLogger : public EnhancedLogger
{
public:
    explicit SQLLogger(std::unique_ptr<Logger> logger)
        : EnhancedLogger(std::move(logger))
    {
        m_description = "SQL Logger";
    }

    void log(const std::string& event) const override
    {
        m_logger->log(event);
        SQLLog(event);
    }

    std::string getDescription() const override
    {
        return m_logger->getDescription() + " + SQL Logger";
    }

private:
    void SQLLog(const std::string& event) const
    {
        std::cout << event << " logged into SQL database" << std::endl;
    }
};

// Concrete Decorator - HTML Logger
class HTMLLogger : public EnhancedLogger
{
public:
    explicit HTMLLogger(std::unique_ptr<Logger> logger)
        : EnhancedLogger(std::move(logger))
    {
        m_description = "HTML Logger";
    }

    void log(const std::string& event) const override
    {
        m_logger->log(event);
        HTMLLog(event);
    }

    std::string getDescription() const override
    {
        return m_logger->getDescription() + " + HTML Logger";
    }

private:
    void HTMLLog(const std::string& event) const
    {
        std::cout << event << " logged into HTML file" << std::endl;
    }
};

int main()
{
    // Create a base file logger
    std::unique_ptr<Logger> logger = std::make_unique<FileLogger>();

    // Decorate with SQL logging
    logger = std::make_unique<SQLLogger>(std::move(logger));

    // Decorate with HTML logging
    logger = std::make_unique<HTMLLogger>(std::move(logger));

    // Display description and log an event
    std::cout << logger->getDescription() << std::endl;
    logger->log("User login event");

    return 0;
}
