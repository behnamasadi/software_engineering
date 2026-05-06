// Object Pool — thread-safe variant.
//
// acquire() blocks on a condition_variable when the pool is empty, then
// hands out a shared_ptr whose custom deleter returns the resource and
// notifies one waiter.

#include <chrono>
#include <condition_variable>
#include <iostream>
#include <memory>
#include <mutex>
#include <queue>
#include <thread>
#include <utility>
#include <vector>

class Resource {
public:
    explicit Resource(int id) : id_(id) {
        std::cout << "  Resource " << id_ << " created\n";
    }
    ~Resource() { std::cout << "  Resource " << id_ << " destroyed\n"; }

    void use() const { std::cout << "  using Resource " << id_ << '\n'; }

private:
    int id_;
};

class ObjectPool {
public:
    explicit ObjectPool(std::size_t size) {
        for (std::size_t i = 0; i < size; ++i) {
            pool_.push(std::make_unique<Resource>(static_cast<int>(i)));
        }
    }

    std::shared_ptr<Resource> acquire() {
        std::unique_lock<std::mutex> lock(mutex_);
        cv_.wait(lock, [this] { return !pool_.empty(); });

        std::unique_ptr<Resource> resource = std::move(pool_.front());
        pool_.pop();

        // Caller must drop the shared_ptr before the pool dies.
        return std::shared_ptr<Resource>(resource.release(),
            [this](Resource* r) { release(r); });
    }

private:
    void release(Resource* r) {
        {
            std::lock_guard<std::mutex> lock(mutex_);
            pool_.emplace(r);
        }
        cv_.notify_one();
        std::cout << "  -> returned to pool\n";
    }

    std::queue<std::unique_ptr<Resource>> pool_;
    std::mutex mutex_;
    std::condition_variable cv_;
};

void worker(ObjectPool& pool, int id) {
    auto resource = pool.acquire();
    std::cout << "  worker " << id << " acquired a resource\n";
    resource->use();
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    std::cout << "  worker " << id << " done\n";
}

int main() {
    ObjectPool pool(3);  // 3 resources, 4 workers — one will wait

    std::vector<std::thread> threads;
    for (int i = 1; i <= 4; ++i) {
        threads.emplace_back(worker, std::ref(pool), i);
    }
    for (auto& t : threads) t.join();
}
