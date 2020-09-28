#include <iostream>
#include <string>

class Logger
{
protected:
    std::string m_description;
public:
    Logger()
    {
        m_description="Unkown Logger";
    }
    virtual void log(std::string event)
    {
        std::cout<<event+ "logged" <<std::endl;
    }

    virtual std::string getDescription()
    {
        return m_description;
    }
};

class FileLogger:public Logger
{
public:
    FileLogger()
    {
        m_description="File logger";
    }

    void log(std::string event) override
    {
        std::cout<<event+ "logged into file" <<std::endl;
    }
};

class LoggerDecorator:public Logger
{
protected:
    Logger *m_logger;
public:
    LoggerDecorator(Logger *logger):m_logger(logger){}
    virtual std::string getDescription() = 0;
    virtual void log(std::string event) = 0;
};

class SQL: public LoggerDecorator
{

public:
    SQL(Logger *logger):LoggerDecorator(logger)
    {
        m_description="SQL Logger";
    }

    void log(std::string event) override
    {
        m_logger->log(event);
        SQLLog(event);
    }

    std::string getDescription() override
    {
        return  m_logger->getDescription()+ " + SQL logger";
    }
    void SQLLog(std::string event)
    {
        std::cout<<event+ " logged into sql" <<std::endl;
    }
};

class HTML: public LoggerDecorator
{

public:
    HTML(Logger *logger):LoggerDecorator(logger)
    {
        m_description="HTML Logger";
    }

    std::string getDescription() override
    {
        return  m_logger->getDescription()+ " + HTML logger";
    }

    void HTMLLog(std::string event)
    {
        std::cout<<event+" logged into html file" <<std::endl;
    }

    void log(std::string event) override
    {
        m_logger->log(event);
        HTMLLog(event);
    }
};
int main()
{
    Logger *file_logger=new FileLogger() ;
    Logger *file_logger_sql=new SQL(file_logger);
    Logger *file_logger_sql_html=new HTML(file_logger_sql);

    std::cout<<file_logger_sql_html->getDescription()<<std::endl;
    file_logger_sql_html->log("some event");
}

