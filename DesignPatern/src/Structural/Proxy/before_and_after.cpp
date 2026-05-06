// Proxy — virtual proxy for lazy loading.
//
// Before: every Image is constructed eagerly, even if the client never
// renders it. With 5 images, 5 are constructed up front.
//
// After: LazyImage holds no data until the first call to render(); only then
// does it construct the underlying HighResImage. Images that are never
// rendered are never loaded.

#include <iostream>
#include <memory>

namespace before_eager_load {

class Image {
public:
    Image() : id_(next_++) {
        std::cout << "  ctor Image " << id_ << '\n';
    }

    ~Image() { std::cout << "  dtor Image " << id_ << '\n'; }

    void render() const { std::cout << "  render Image " << id_ << '\n'; }

private:
    int id_;
    static int next_;
};

int Image::next_ = 1;

}  // namespace before_eager_load

namespace after_proxy {

class HighResImage {
public:
    explicit HighResImage(int id) : id_(id) {
        std::cout << "  loaded HighResImage " << id_ << '\n';
    }

    ~HighResImage() { std::cout << "  unloaded HighResImage " << id_ << '\n'; }

    void render() const { std::cout << "  render HighResImage " << id_ << '\n'; }

private:
    int id_;
};

class LazyImage {
public:
    LazyImage() : id_(next_++) {}

    void render() {
        if (!real_) {
            std::cout << "  lazy-loading image " << id_ << '\n';
            real_ = std::make_unique<HighResImage>(id_);
        }
        real_->render();
    }

private:
    int id_;
    std::unique_ptr<HighResImage> real_;
    static int next_;
};

int LazyImage::next_ = 1;

}  // namespace after_proxy

int main() {
    std::cout << "=== Before (eager construction) ===\n";
    {
        before_eager_load::Image images[3];
        std::cout << "rendering only image 1:\n";
        images[0].render();
    }

    std::cout << "\n=== After (lazy proxy) ===\n";
    {
        after_proxy::LazyImage images[3];
        std::cout << "rendering only image 1 (only image 1 gets loaded):\n";
        images[0].render();
        std::cout << "rendering image 1 again (already loaded, no reload):\n";
        images[0].render();
    }
}
