// Command — queueing variant.
// A Task captures (receiver, action) so it can sit in a queue and be run later.

#include <deque>
#include <iostream>
#include <memory>

class Worker {
public:
    Worker() : id_(nextId_++) {}

    void alpha() { std::cout << id_ << "-alpha "; }
    void beta()  { std::cout << id_ << "-beta  "; }
    void gamma() { std::cout << id_ << "-gamma "; }

private:
    int id_;
    static int nextId_;
};
int Worker::nextId_ = 0;

class Task {
public:
    using Action = void (Worker::*)();
    Task(Worker& worker, Action action) : worker_(worker), action_(action) {}
    void execute() { (worker_.*action_)(); }
private:
    Worker& worker_;
    Action action_;
};

int main() {
    Worker w1, w2;

    std::deque<Task> queue;
    queue.emplace_back(w1, &Worker::alpha);
    queue.emplace_back(w2, &Worker::beta);
    queue.emplace_back(w1, &Worker::gamma);
    queue.emplace_back(w2, &Worker::alpha);

    while (!queue.empty()) {
        queue.front().execute();
        queue.pop_front();
    }
    std::cout << '\n';
}
