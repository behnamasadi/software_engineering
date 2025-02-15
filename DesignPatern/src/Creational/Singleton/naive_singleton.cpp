#include <iostream>
#include <thread>
#include <memory>
#include <mutex>

using namespace std;

class Singleton {
private:
    static std::unique_ptr<Singleton> instance;
    static std::mutex mtx;
    std::string value_;

    explicit Singleton(const std::string& value) : value_(value) {}

public:
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

    static Singleton* GetInstance(const std::string& value) {
        std::lock_guard<std::mutex> lock(mtx);
        if (!instance) {
            instance = std::unique_ptr<Singleton>(new Singleton(value));
        }
        return instance.get();
    }

    void SomeBusinessLogic() {
        // Business logic implementation
    }

    std::string value() const {
        return value_;
    }
};

std::unique_ptr<Singleton> Singleton::instance = nullptr;
std::mutex Singleton::mtx;

void ThreadFoo() {
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    Singleton* singleton = Singleton::GetInstance("FOO");
    std::cout << singleton->value() << "\n";
}

void ThreadBar() {
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    Singleton* singleton = Singleton::GetInstance("BAR");
    std::cout << singleton->value() << "\n";
}

int main() {
    std::cout << "If you see the same value, then singleton was reused (yay!)\n"
              << "If you see different values, then 2 singletons were created (booo!!)\n\n"
              << "RESULT:\n";
    
    std::thread t1(ThreadFoo);
    std::thread t2(ThreadBar);
    t1.join();
    t2.join();
    
    return 0;
}
