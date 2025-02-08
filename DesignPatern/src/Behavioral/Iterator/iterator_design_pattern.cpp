#include <iostream>
#include <memory>
#include <vector>

// 1. Data Structure: Sensor Data Point
struct SensorData {
  double timestamp;
  double x, y, z;

  SensorData(double t, double x, double y, double z)
      : timestamp(t), x(x), y(y), z(z) {}
};

// 2. Iterator Interface
class Iterator {
public:
  virtual bool hasNext() = 0;
  virtual SensorData *next() = 0;
  virtual ~Iterator() = default;
};

// 3. Concrete Iterator for Sensor Data Collection
class SensorDataIterator : public Iterator {
private:
  std::vector<SensorData> &data;
  size_t index;

public:
  explicit SensorDataIterator(std::vector<SensorData> &d) : data(d), index(0) {}

  bool hasNext() override { return index < data.size(); }

  SensorData *next() override { return hasNext() ? &data[index++] : nullptr; }
};

// 4. Collection Class
class SensorDataCollection {
private:
  std::vector<SensorData> data;

public:
  void addData(double t, double x, double y, double z) {
    data.emplace_back(t, x, y, z);
  }

  std::unique_ptr<Iterator> createIterator() {
    return std::make_unique<SensorDataIterator>(data);
  }
};

// 5. Client Code
int main() {
  SensorDataCollection collection;
  collection.addData(1.0, 0.1, 0.2, 0.3);
  collection.addData(2.0, 1.1, 1.2, 1.3);
  collection.addData(3.0, 2.1, 2.2, 2.3);

  auto iterator = collection.createIterator();

  while (iterator->hasNext()) {
    SensorData *data = iterator->next();
    std::cout << "Timestamp: " << data->timestamp << ", Position: (" << data->x
              << ", " << data->y << ", " << data->z << ")\n";
  }

  return 0;
}
