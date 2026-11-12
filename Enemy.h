#pragma once
struct Enemy
{
    int x;
    int y;

    private:
    int health;

    public:
    Enemy(int start_x, int start_y, int start_health);

    int get_health() const;

    void take_damage(int damage);

    bool is_alive() const;

};
