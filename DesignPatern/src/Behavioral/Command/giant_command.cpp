#include <iostream>
#include <vector>
#include <memory>

class Colossus
{
public:
    Colossus() { m_id = s_next++; }

    void alpha() { std::cout << m_id << "-alpha  "; }
    void beta() { std::cout << m_id << "-beta  "; }
    void gamma() { std::cout << m_id << "-gamma  "; }

private:
    int m_id;
    static int s_next;
};

int Colossus::s_next = 0;

class Task
{
public:
    using Action = void(Colossus::*)();

    Task(Colossus *object, Action method) : m_object(object), m_method(method) {}

    void execute() { (m_object->*m_method)(); }

private:
    Colossus *m_object;
    Action m_method;
};

template <typename T>
class TaskQueue
{
public:
    void enqueue(std::unique_ptr<T> task)
    {
        m_tasks.push_back(std::move(task));
    }

    std::unique_ptr<T> dequeue()
    {
        if (m_tasks.empty())
            return nullptr;

        std::unique_ptr<T> task = std::move(m_tasks.front());
        m_tasks.erase(m_tasks.begin());
        return task;
    }

private:
    std::vector<std::unique_ptr<T>> m_tasks;
};

int main()
{
    TaskQueue<Task> queue;
    
    std::vector<std::unique_ptr<Task>> commands;
    commands.emplace_back(std::make_unique<Task>(new Colossus, &Colossus::alpha));
    commands.emplace_back(std::make_unique<Task>(new Colossus, &Colossus::beta));
    commands.emplace_back(std::make_unique<Task>(new Colossus, &Colossus::gamma));
    commands.emplace_back(std::make_unique<Task>(new Colossus, &Colossus::alpha));
    commands.emplace_back(std::make_unique<Task>(new Colossus, &Colossus::beta));
    commands.emplace_back(std::make_unique<Task>(new Colossus, &Colossus::gamma));

    for (auto &cmd : commands)
        queue.enqueue(std::move(cmd));

    for (int i = 0; i < 6; i++)
    {
        auto task = queue.dequeue();
        if (task)
            task->execute();
    }
    
    std::cout << '\n';

    return 0;
}
