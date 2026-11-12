#pragma once
struct Player
{
    int x = 1;
    int y = 1;
    int score = 0;
    

    void take_damage(int damage);
  

    bool is_alive() const;
    int get_health() const;

    private:
        int health = 3;
};