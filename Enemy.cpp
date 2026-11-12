#include "Enemy.h"
#include <stdexcept>


 Enemy::Enemy(int start_x, int start_y, int start_health)
    : x(start_x), y(start_y), health(start_health)
    {
        if (start_health < 0)
            throw std::invalid_argument("Zdrowie nie może być ujemne!");
    }

    void Enemy::take_damage(int damage)
    {
        if (damage < 0)
            throw std::invalid_argument("Obrażenia nie mogą być ujemne!");
        
        this->health -=damage;
        if(this->health < 0)
            this->health = 0;
    }

    bool Enemy::is_alive() const
{
    return this->health>0;
}

    int Enemy::get_health() const
    {
        return this->health;
    }