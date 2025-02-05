#include <iostream>


class Monster {
public:
    std::string name = "unknown";
    int health = 100;
    int attackDamage = 10;

    void attack() {
        std::cout << name << " attack: " << attackDamage << std::endl;
    }


};

class FlyingMonster : public Monster
{
public:
    double flightSpeed = 50;
    void fly() {
        std::cout << name << " fly: " << flightSpeed << std::endl;
    }
};

class ShootingMonster : public Monster
{
public:
    double attackRange = 30;
    void shoot() {
        attack();
        std::cout << name << " shooting: " << attackRange << std::endl;
    }
};




int main() {

    FlyingMonster* bird = new FlyingMonster();

    bird->fly();
    bird->attack();
    delete bird;
    return 0;
}