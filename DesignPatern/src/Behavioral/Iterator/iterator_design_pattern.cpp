// Iterator — traverse a collection without exposing its internal layout.
//
// In modern C++ you'd usually rely on standard begin()/end() and range-for.
// This example shows the GoF interface explicitly so the moving parts are
// visible: an Iterator interface (hasNext/next) and a Collection that hands
// one out via createIterator().

#include <iostream>
#include <memory>
#include <vector>

struct SensorReading {
    double timestamp;
    double x, y, z;
};

class Iterator {
public:
    virtual ~Iterator() = default;
    virtual bool hasNext() const = 0;
    virtual const SensorReading& next() = 0;
};

class SensorLog {
public:
    void add(SensorReading reading) { data_.push_back(reading); }

    std::unique_ptr<Iterator> iterator() const {
        return std::make_unique<LogIterator>(data_);
    }

private:
    class LogIterator : public Iterator {
    public:
        explicit LogIterator(const std::vector<SensorReading>& data) : data_(data) {}
        bool hasNext() const override { return index_ < data_.size(); }
        const SensorReading& next() override { return data_[index_++]; }
    private:
        const std::vector<SensorReading>& data_;
        std::size_t index_ = 0;
    };

    std::vector<SensorReading> data_;
};

int main() {
    SensorLog log;
    log.add({1.0, 0.1, 0.2, 0.3});
    log.add({2.0, 1.1, 1.2, 1.3});
    log.add({3.0, 2.1, 2.2, 2.3});

    auto it = log.iterator();
    while (it->hasNext()) {
        const auto& r = it->next();
        std::cout << "t=" << r.timestamp
                  << " (" << r.x << ", " << r.y << ", " << r.z << ")\n";
    }
}
