// Chain of Responsibility — image processing pipeline.
// Unlike the typical "first handler wins" variant, every step in the chain
// runs in order. This is the pipeline flavor of the same pattern.

#include <iostream>
#include <string>

struct Photo {
    std::string name;
};

class PhotoProcessor {
public:
    virtual ~PhotoProcessor() = default;

    void setNext(PhotoProcessor* next) { next_ = next; }

    void process(Photo& photo) {
        apply(photo);
        if (next_) next_->process(photo);
    }

protected:
    virtual void apply(Photo& photo) = 0;

private:
    PhotoProcessor* next_ = nullptr;
};

class RedEyeRemoval : public PhotoProcessor {
protected:
    void apply(Photo& photo) override {
        std::cout << "[" << photo.name << "] removing red-eye\n";
    }
};

class Scale : public PhotoProcessor {
public:
    Scale(int width, int height) : width_(width), height_(height) {}
protected:
    void apply(Photo& photo) override {
        std::cout << "[" << photo.name << "] scaling to "
                  << width_ << "x" << height_ << '\n';
    }
private:
    int width_, height_;
};

class MeanFilter : public PhotoProcessor {
public:
    explicit MeanFilter(int kernel) : kernel_(kernel) {}
protected:
    void apply(Photo& photo) override {
        std::cout << "[" << photo.name << "] mean filter k=" << kernel_ << '\n';
    }
private:
    int kernel_;
};

int main() {
    RedEyeRemoval redEye;
    Scale scale(800, 600);
    MeanFilter blur(3);

    redEye.setNext(&scale);
    scale.setNext(&blur);

    Photo photo{"vacation.jpg"};
    redEye.process(photo);
}
