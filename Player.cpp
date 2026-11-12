#include "Player.h"
#include <stdexcept>

void Player::take_damage(int damage)
{
     if (damage < 0)
            throw std::invalid_argument("Obrażenia nie mogą być ujemne!");
        
        this->health -=damage;
        if(this->health < 0)
            this->health = 0;
}

bool Player::is_alive() const
{
    return this->health>0;
}

int Player::get_health() const
{
    return this->health;
}