#include <iostream>
#include <memory>
#include <unordered_map>
#include <string>

enum class BulletType
{
    SIMPLE,
    EXPLOSIVE
};

class Bullet
{
protected:
    std::string name;
    double speed;
    double firePower;
    double damagePower;
    int id;

public:
    static int counter;
    virtual ~Bullet() = default;
    Bullet(std::string name, double speed, double firePower, double damagePower)
        : name(std::move(name)), speed(speed), firePower(firePower), damagePower(damagePower), id(counter++) {}

    virtual std::unique_ptr<Bullet> clone() const = 0;

    void fire(double direction) const
    {
        std::cout << "Bullet ID: " << id << "\n"
                  << "Name: " << name << "\n"
                  << "Speed: " << speed << "\n"
                  << "Fire Power: " << firePower << "\n"
                  << "Damage Power: " << damagePower << "\n"
                  << "Direction: " << direction << "\n";
    }
};

int Bullet::counter = 0;

class ExplosiveBullet : public Bullet
{
public:
    ExplosiveBullet(std::string bulletName, double speed, double firePower, double damagePower)
        : Bullet(std::move(bulletName), speed, firePower, damagePower) {}

    std::unique_ptr<Bullet> clone() const override
    {
        return std::make_unique<ExplosiveBullet>(*this);
    }
};

class SimpleBullet : public Bullet
{
public:
    SimpleBullet(std::string bulletName, double speed, double firePower, double damagePower)
        : Bullet(std::move(bulletName), speed, firePower, damagePower) {}

    std::unique_ptr<Bullet> clone() const override
    {
        return std::make_unique<SimpleBullet>(*this);
    }
};

class BulletFactory
{
private:
    std::unordered_map<BulletType, std::unique_ptr<Bullet>> bullets;

public:
    BulletFactory()
    {
        bullets[BulletType::SIMPLE] = std::make_unique<SimpleBullet>("Simple Bullet", 10.0, 15.0, 1.0);
        bullets[BulletType::EXPLOSIVE] = std::make_unique<ExplosiveBullet>("Explosive Bullet", 10.0, 50.0, 10.0);
    }

    std::unique_ptr<Bullet> createBullet(BulletType type) const
    {
        auto it = bullets.find(type);
        if (it != bullets.end())
        {
            return it->second->clone();
        }
        return nullptr;
    }
};

int main()
{
    BulletFactory bf;
    auto simpleBullet = bf.createBullet(BulletType::SIMPLE);
    if (simpleBullet)
        simpleBullet->fire(45);

    auto explosiveBullet = bf.createBullet(BulletType::EXPLOSIVE);
    if (explosiveBullet)
    {
        explosiveBullet->fire(30);
        explosiveBullet->fire(15);
        for (int i = 0; i < 10; ++i)
        {
            explosiveBullet->fire(i * 10);
        }
    }
}
