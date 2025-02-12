#include <iostream>
#include <memory>

class MotionBehavior;
class ColorBehavior;

class ScreenBall {
private:
    std::unique_ptr<MotionBehavior> motionBehavior;
    std::unique_ptr<ColorBehavior> colorBehavior;

public:
    void setMotionBehavior(std::unique_ptr<MotionBehavior> strategy) {
        motionBehavior = std::move(strategy);
    }

    void setColorBehavior(std::unique_ptr<ColorBehavior> strategy) {
        colorBehavior = std::move(strategy);
    }

    void applyStrategies();
};

class MotionBehavior {
public:
    virtual void move(ScreenBall& ball) = 0;
    virtual ~MotionBehavior() = default;
};

class ColorBehavior {
public:
    virtual void changeColor(ScreenBall& ball) = 0;
    virtual ~ColorBehavior() = default;
};

class StaticMotion : public MotionBehavior {
public:
    void move(ScreenBall& ball) override {
        // Does nothing (Null Object)
    }
};

class DefaultColor : public ColorBehavior {
public:
    void changeColor(ScreenBall& ball) override {
        // No color change (Null Object)
    }
};

void ScreenBall::applyStrategies() {
    if (motionBehavior) motionBehavior->move(*this);
    if (colorBehavior) colorBehavior->changeColor(*this);
}

int main() {
    ScreenBall ball;

    // Setting Null Object Strategies
    ball.setMotionBehavior(std::make_unique<StaticMotion>());
    ball.setColorBehavior(std::make_unique<DefaultColor>());

    // Applying strategies (should do nothing)
    ball.applyStrategies();

    return 0;
}
