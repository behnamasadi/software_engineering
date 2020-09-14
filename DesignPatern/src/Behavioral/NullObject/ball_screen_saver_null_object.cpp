class BallColorStrategy;
class BallMotionStrategy;

class Ball
{
private:
    BallMotionStrategy * ballMotionStrategy ;
    BallColorStrategy *ballColorStrategy;
public:
    void setBallColorStrategy(BallColorStrategy *){}
    void setBallMotionStrategy(BallMotionStrategy*){}

};

class BallMotionStrategy
{
public:
    void virtual move(Ball ball)=0;
};

class BallColorStrategy
{
public:
    void virtual changeColor(Ball ball)=0;
};


class NullBallMotionStrategy: public BallMotionStrategy
{
public:
    void move(Ball ball) override{/*do notnigh here*/}
};

class NullBallColorStrategy: public BallColorStrategy
{
public:
    void changeColor(Ball ball)override{/*do notnigh here*/}
};


int main()
{

}
