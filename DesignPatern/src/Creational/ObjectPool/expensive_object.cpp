#include <iostream>
#include <vector>
#include <memory>
#include <mutex>

// ExpensiveObject: Represents an object that is costly to create.
class ExpensiveObject {
public:
    ExpensiveObject() {
        std::cout << "ExpensiveObject created.\n";
    }

    void use() {
        std::cout << "Using ExpensiveObject.\n";
    }

    ~ExpensiveObject() {
        std::cout << "ExpensiveObject destroyed.\n";
    }
};

// ObjectPool: Manages a pool of reusable objects.
class ObjectPool {
private:
    std::vector<std::unique_ptr<ExpensiveObject>> availableObjects;
    std::mutex mtx;  // To make the pool thread-safe

public:
    // Get an object from the pool
    std::shared_ptr<ExpensiveObject> acquire() {
        std::lock_guard<std::mutex> lock(mtx);  // Lock for thread safety

        if (!availableObjects.empty()) {
            // Reuse an existing object
            std::unique_ptr<ExpensiveObject> obj = std::move(availableObjects.back());
            availableObjects.pop_back();

            // Wrap it in a shared_ptr with a custom deleter that returns it to the pool
            return std::shared_ptr<ExpensiveObject>(obj.release(), [this](ExpensiveObject* objPtr) {
                release(objPtr);
            });
        }

        // If no available objects, create a new one
        return std::shared_ptr<ExpensiveObject>(new ExpensiveObject(), [this](ExpensiveObject* objPtr) {
            release(objPtr);
        });
    }

private:
    // Release an object back into the pool
    void release(ExpensiveObject* objPtr) {
        std::lock_guard<std::mutex> lock(mtx);  // Lock for thread safety
        availableObjects.push_back(std::unique_ptr<ExpensiveObject>(objPtr));
        std::cout << "Object returned to pool.\n";
    }
};

// Demonstration of Object Pool Usage
int main() {
    ObjectPool pool;

    // Acquire objects
    auto obj1 = pool.acquire();
    obj1->use();

    auto obj2 = pool.acquire();
    obj2->use();

    // Objects are automatically returned to the pool when they go out of scope
    obj1.reset(); // Explicitly returning obj1 to the pool
    auto obj3 = pool.acquire(); // Reuses obj1 instead of creating a new one

    return 0;
}
