#include <iostream>
#include <memory>
#include <ctime>
#include <thread>
#include <mutex>

class Logger {
private:
    static std::unique_ptr<Logger> instance;
    static std::mutex mtx;
    std::string logData;

    // Private constructor
    Logger() = default;
    
    // Deleted copy constructor and assignment operator
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

public:
    static Logger* getInstance() {
        std::lock_guard<std::mutex> lock(mtx);
        if (!instance) {
            instance.reset(new Logger());  // Using reset() instead of make_unique()
        }
        return instance.get();
    }

    void logEvent(const std::string& event) {
        std::time_t now = std::time(nullptr);
        std::tm* ptm = std::localtime(&now);
        char buffer[32];
        std::strftime(buffer, 32, "%a, %d.%m.%Y %H:%M:%S", ptm);
        logData.append(buffer);
        logData.append(" - " + event + "\n");
    }

    std::string getLogs() const {
        return logData;
    }
};

// Initialize static members
std::unique_ptr<Logger> Logger::instance = nullptr;
std::mutex Logger::mtx;

void func1() {
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    Logger::getInstance()->logEvent("func1 called");
}

void func2() {
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    Logger::getInstance()->logEvent("func2 called");
}

int main() {
    Logger::getInstance()->logEvent("main called");

    std::thread t1(func1);
    std::thread t2(func2);

    t1.join();
    t2.join();

    std::cout << Logger::getInstance()->getLogs() << std::endl;
    return 0;
}
