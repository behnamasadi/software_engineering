// Null Object — combined with Strategy.
// A screen-saver ball delegates motion and color to strategy objects. Instead
// of allowing null strategies (forcing every call site to check), we use
// no-op "null" strategies. Ball::tick() never needs an if-guard.

#include <iostream>
#include <memory>
#include <utility>

class Ball;

class MotionStrategy {
public:
    virtual ~MotionStrategy() = default;
    virtual void move(Ball& ball) = 0;
};

class ColorStrategy {
public:
    virtual ~ColorStrategy() = default;
    virtual void recolor(Ball& ball) = 0;
};

class StaticMotion : public MotionStrategy {
public:
    void move(Ball&) override { /* null object: do nothing */ }
};

class FixedColor : public ColorStrategy {
public:
    void recolor(Ball&) override { /* null object: do nothing */ }
};

class BouncingMotion : public MotionStrategy {
public:
    void move(Ball&) override { std::cout << "  bouncing\n"; }
};

class RainbowColor : public ColorStrategy {
public:
    void recolor(Ball&) override { std::cout << "  recoloring\n"; }
};

class Ball {
public:
    Ball()
        : motion_(std::make_unique<StaticMotion>()),
          color_(std::make_unique<FixedColor>()) {}

    void setMotion(std::unique_ptr<MotionStrategy> m) { motion_ = std::move(m); }
    void setColor(std::unique_ptr<ColorStrategy> c)   { color_  = std::move(c); }

    void tick() {
        std::cout << "tick:\n";
        motion_->move(*this);     // no nullptr check needed — guaranteed non-null
        color_->recolor(*this);
    }

private:
    std::unique_ptr<MotionStrategy> motion_;
    std::unique_ptr<ColorStrategy>  color_;
};

int main() {
    Ball ball;
    ball.tick();  // both behaviors are null objects: prints nothing inside

    ball.setMotion(std::make_unique<BouncingMotion>());
    ball.setColor(std::make_unique<RainbowColor>());
    ball.tick();
}
