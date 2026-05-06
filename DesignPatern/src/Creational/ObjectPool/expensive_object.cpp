// Object Pool — reuse instances of an expensive-to-create type.
//
// acquire() hands out a shared_ptr whose custom deleter returns the object
// to the pool instead of destroying it. Clients use the resource normally
// and the pool gets it back when the shared_ptr is dropped.

#include <iostream>
#include <memory>
#include <mutex>
#include <vector>

class ExpensiveObject {
public:
    ExpensiveObject() { std::cout << "  ExpensiveObject created\n"; }
    ~ExpensiveObject() { std::cout << "  ExpensiveObject destroyed\n"; }

    void use() { std::cout << "  using ExpensiveObject\n"; }
};

class ObjectPool {
public:
    std::shared_ptr<ExpensiveObject> acquire() {
        std::lock_guard<std::mutex> lock(mutex_);

        std::unique_ptr<ExpensiveObject> obj;
        if (!available_.empty()) {
            obj = std::move(available_.back());
            available_.pop_back();
        } else {
            obj = std::make_unique<ExpensiveObject>();
        }

        // Custom deleter returns the object to the pool instead of deleting it.
        // Note: caller must drop the returned shared_ptr before the pool is
        // destroyed. (For a fully-safe variant, hold a weak_ptr to the pool.)
        return std::shared_ptr<ExpensiveObject>(obj.release(),
            [this](ExpensiveObject* p) { release(p); });
    }

private:
    void release(ExpensiveObject* p) {
        std::lock_guard<std::mutex> lock(mutex_);
        available_.emplace_back(p);
        std::cout << "  -> returned to pool\n";
    }

    std::vector<std::unique_ptr<ExpensiveObject>> available_;
    std::mutex mutex_;
};

int main() {
    ObjectPool pool;

    auto obj1 = pool.acquire();
    obj1->use();

    auto obj2 = pool.acquire();
    obj2->use();

    obj1.reset();                // returns to pool
    auto obj3 = pool.acquire();  // reuses the freed slot — no new construction
    obj3->use();
}
