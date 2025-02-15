#include <iostream>
#include <queue>
#include <memory>
#include <mutex>
#include <condition_variable>
#include <thread>

// Resource class simulating an expensive object.
class Resource {
public:
    Resource(int id) : id(id) {
        std::cout << "Resource " << id << " created.\n";
    }

    void use() {
        std::cout << "Using Resource " << id << ".\n";
    }

    ~Resource() {
        std::cout << "Resource " << id << " destroyed.\n";
    }

private:
    int id;
};

// Thread-safe Object Pool
class ObjectPool {
public:
    ObjectPool(size_t poolSize) {
        for (size_t i = 0; i < poolSize; ++i) {
            pool.push(std::make_unique<Resource>(i));
        }
    }

    std::shared_ptr<Resource> acquire() {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [this] { return !pool.empty(); });

        // Extract unique_ptr and convert it to a shared_ptr with a custom deleter
        std::unique_ptr<Resource> uniqueResource = std::move(pool.front());
        pool.pop();

        return std::shared_ptr<Resource>(uniqueResource.release(), [this](Resource* r) {
            release(r);
        });
    }

private:
    void release(Resource* resource) {
        std::lock_guard<std::mutex> lock(mtx);
        pool.push(std::unique_ptr<Resource>(resource));
        cv.notify_one();
        std::cout << "Resource returned to pool.\n";
    }

    std::queue<std::unique_ptr<Resource>> pool;
    std::mutex mtx;
    std::condition_variable cv;
};

// Function to simulate multiple threads using the pool
void worker(ObjectPool& pool, int workerID) {
    auto resource = pool.acquire();
    std::cout << "Worker " << workerID << " acquired a resource.\n";
    resource->use();
    std::this_thread::sleep_for(std::chrono::milliseconds(500)); // Simulate work
    std::cout << "Worker " << workerID << " done using the resource.\n";
}

int main() {
    ObjectPool pool(3); // Pool with 3 resources

    std::thread t1(worker, std::ref(pool), 1);
    std::thread t2(worker, std::ref(pool), 2);
    std::thread t3(worker, std::ref(pool), 3);
    std::thread t4(worker, std::ref(pool), 4); // Will wait for a resource

    t1.join();
    t2.join();
    t3.join();
    t4.join();

    return 0;
}
