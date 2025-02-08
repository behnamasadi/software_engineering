#include <iostream>
#include <string>

class Photo {};

class PhotoProcessor {
protected:
  PhotoProcessor *next;

public:
  PhotoProcessor() : next(nullptr) {}

  virtual ~PhotoProcessor() = default; // Virtual destructor

  void setNext(PhotoProcessor *nextProcessor) { next = nextProcessor; }

  void process(Photo *photo) {
    processImplementation(photo);
    if (next != nullptr)
      next->process(photo);
  }

  virtual void processImplementation(
      Photo *photo) = 0; // Correct syntax for pure virtual function
};

class RedEye : public PhotoProcessor {
public:
  RedEye() = default; // No need to explicitly initialize next

  void processImplementation(Photo *photo) override {
    std::cout << "Correcting red eye" << std::endl;
  }
};

class Scaling : public PhotoProcessor {
private:
  int width, height;

public:
  Scaling(int width, int height) : width(width), height(height) {}

  void processImplementation(Photo *photo) override {
    std::cout << "Scaling to " << width << "x" << height << std::endl;
  }
};

class MeanFilter : public PhotoProcessor {
private:
  double mean, var;

public:
  MeanFilter(double mean, double var) : mean(mean), var(var) {}

  void processImplementation(Photo *photo) override {
    std::cout << "Applying mean filter with mean " << mean << ", variance "
              << var << std::endl;
  }
};

int main() {
  Photo myPhoto;

  RedEye redEyeProcessor;
  Scaling scalingProcessor(600, 800);
  MeanFilter meanFilterProcessor(0.0, 1.0);

  // Creating the processing chain
  redEyeProcessor.setNext(&scalingProcessor);
  scalingProcessor.setNext(&meanFilterProcessor);

  // Start processing
  redEyeProcessor.process(&myPhoto);

  return 0;
}
