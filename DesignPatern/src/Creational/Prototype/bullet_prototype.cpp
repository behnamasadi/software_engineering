#include <string>
#include <iostream>
#include <memory>
#include <unordered_map>


enum BulletType
{
    SIMPLE,
    EXPLOSIVE
};

class Bullet
{
    std::string name;
    double speed;
    double firePower;
    double damgePower;
    double direction;
    int id;

public:
    static int counter;
    void fire(double direction)
    {
        std::cout<<"id: "<<id<<"\n"
                 <<"name: "<<name <<"\n"
                 << "speed: "<< speed<<"\n"
                 << "firePower: "<<firePower<<"\n"
                 << "damgePower: "<<damgePower<<"\n"
                 << "direction: "<<direction <<std::endl;
    }

    virtual std::unique_ptr<Bullet> clone()=0;
    virtual ~Bullet(){}
    Bullet(std::string name, double speed, double firePower, double damgePower)
        :name(name), speed(speed), firePower(firePower),damgePower(damgePower)
    {
        id=counter;
        counter++;
    }
};


class ExplosiveBullet: public Bullet
{
public:

    std::unique_ptr<Bullet> clone() override
    {
        return std::make_unique<ExplosiveBullet>(*this);
    }

    ExplosiveBullet(std::string bulletName, double  speed, double  firePower, double  damagePower)
        : Bullet(bulletName, speed, firePower, damagePower)
        {
        }
};

class SimpleBullet: public Bullet
{
public:
    std::unique_ptr<Bullet> clone() override
    {
        return std::make_unique<SimpleBullet>(*this);
    }
    SimpleBullet(std::string bulletName, double speed, double  firePower, double  damagePower)
        : Bullet(bulletName, speed, firePower, damagePower)
        {
        }
};

class BulletFactory
{
private:
    //Unordered map is an associative container that contains key-value pairs with unique keys
    std::unordered_map<BulletType, std::unique_ptr<Bullet>,std::hash<int> > bullets;
public:
    BulletFactory()
    {
        std::string name;
        double speed;
        double firePower;
        double damgePower;
        double direction;

        name="simple bullet";
        speed=10;
        firePower=15;
        damgePower=1;
        bullets[BulletType::SIMPLE]=std::make_unique<SimpleBullet>(name,speed,firePower,damgePower);

        name="explosive bullet";
        speed=10;
        firePower=50;
        damgePower=10;

        bullets[BulletType::EXPLOSIVE]=std::make_unique<ExplosiveBullet>(name,speed,firePower,damgePower);
    }
    std::unique_ptr<Bullet> createBullet(BulletType type)
    {
        return bullets[type]->clone();
    }
};

int Bullet::counter=0;

int main()
{
    BulletFactory bf;
    std::unique_ptr<Bullet> simplebullet=  bf.createBullet(BulletType::SIMPLE);
    simplebullet->fire(45);

    std::unique_ptr<Bullet> explosivebullet=  bf.createBullet(BulletType::EXPLOSIVE);
    explosivebullet->fire(30);

    explosivebullet->fire(15);
    for(std::size_t i=0;i<10;i++)
    {
        explosivebullet->fire(i);
    }

}
