#pragma once
#include <vector>
#include <string>
#include "Player.h"
#include "Enemy.h"

struct Game
{
    int treasures = 0;
    Player player;
    std::vector<Enemy> enemies = {
        Enemy{5,4,2},
        Enemy{7,2,3}
    };
    std::vector<std::string> board = {
        "##########",
        "#@....$..#",
        "#......M.#",
        "#.$.##...#",
        "#....M...#",
        "#.....$..#",
        "#..$.....#",
        "##########",
    };

    void move_player(char direction);

    void display_board() const;

    void display_status() const;

    void count_treasures();

    bool is_won() const;

    bool is_lost() const;

    void run();

};