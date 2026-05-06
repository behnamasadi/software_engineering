// Flyweight — render millions of trees by sharing the heavy bits.
//
// A TreeType holds the intrinsic state — name, color, texture — that's
// expensive to load and identical for every tree of that species. A Tree
// holds only the extrinsic state — its (x, y) position — and a reference to
// its TreeType. Two Oak Trees at different coordinates share the same
// TreeType instead of duplicating it.

#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

// Stand-ins for the heavy assets — color and texture data.
struct Color   {};
struct Texture {};

class Canvas {
public:
    void render(int x, int y, const std::string& tree_type) const {
        std::cout << "  draw " << tree_type << " at (" << x << ", " << y << ")\n";
    }
};

// Flyweight — intrinsic state only.
class TreeType {
public:
    TreeType(std::string name, std::shared_ptr<Color> color,
             std::shared_ptr<Texture> texture)
        : name_(std::move(name)),
          color_(std::move(color)),
          texture_(std::move(texture)) {}

    void render(const Canvas& canvas, int x, int y) const {
        canvas.render(x, y, name_);
    }

private:
    std::string name_;
    std::shared_ptr<Color> color_;
    std::shared_ptr<Texture> texture_;
};

class TreeTypeFactory {
public:
    std::shared_ptr<TreeType> get(const std::string& name,
                                  std::shared_ptr<Color> color,
                                  std::shared_ptr<Texture> texture) {
        auto it = cache_.find(name);
        if (it != cache_.end()) {
            std::cout << "Factory: reusing " << name << '\n';
            return it->second;
        }
        std::cout << "Factory: creating " << name << '\n';
        auto type = std::make_shared<TreeType>(name, std::move(color), std::move(texture));
        cache_[name] = type;
        return type;
    }

private:
    std::unordered_map<std::string, std::shared_ptr<TreeType>> cache_;
};

// Context — extrinsic state plus a reference to the flyweight.
class Tree {
public:
    Tree(int x, int y, std::shared_ptr<TreeType> type)
        : x_(x), y_(y), type_(std::move(type)) {}

    void draw(const Canvas& canvas) const { type_->render(canvas, x_, y_); }

private:
    int x_, y_;
    std::shared_ptr<TreeType> type_;
};

class Forest {
public:
    void plant(int x, int y, const std::string& name) {
        auto type = factory_.get(name, std::make_shared<Color>(),
                                 std::make_shared<Texture>());
        trees_.emplace_back(x, y, std::move(type));
    }

    void render(const Canvas& canvas) const {
        std::cout << "Rendering forest:\n";
        for (const auto& t : trees_) t.draw(canvas);
    }

private:
    std::vector<Tree> trees_;
    TreeTypeFactory factory_;
};

int main() {
    Canvas canvas;
    Forest forest;

    forest.plant(10, 20, "Oak Tree");
    forest.plant(30, 40, "Pine Tree");
    forest.plant(15, 25, "Oak Tree");   // reuses the existing flyweight
    forest.plant(50, 60, "Maple Tree");

    forest.render(canvas);
}
