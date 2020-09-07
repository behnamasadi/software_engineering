#include <iostream>
#include <memory>
#include <ctime>
#include <thread>
#include <unistd.h>// for usleep function

class Logger
{
private:
    static Logger * instance;
    Logger(const Logger&){}
    Logger(){}
    std::string ss;

public:
    static Logger * getInstance()
    {
        if(instance==nullptr)
            instance=new Logger();
        return instance;
    }
    void logEvent(std::string s)
    {
        std::time_t now = std::time(NULL);
        std::tm * ptm = std::localtime(&now);
        char buffer[32];
        // Format: Mo, 15.06.2009 20:20:00
        std::strftime(buffer, 32, "%a, %d.%m.%Y %H:%M:%S", ptm);
        ss.append(buffer);
        ss.append(" "+s+"\n");
    }

    std::string getLogs()
    {
        return ss;
    }

};


Logger *Logger::instance=nullptr;

void func1()
{
    unsigned int numberOfMicroseconds=1000000;
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(std::chrono::microseconds(numberOfMicroseconds));
    Logger * logger=Logger::getInstance();
    logger->logEvent("func1 called");

}

void func2()
{
    unsigned int numberOfMicroseconds=1000000;
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(std::chrono::microseconds(numberOfMicroseconds));
    Logger * logger=Logger::getInstance();
    logger->logEvent("func2 called");

}

int main()
{
    Logger * logger=Logger::getInstance();
    logger->logEvent("main called");
    func1();
    func2();
    std::cout<<logger->getLogs() <<std::endl;
}
