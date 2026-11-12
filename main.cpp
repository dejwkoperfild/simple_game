#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include "Player.h"
#include "Enemy.h"


void fight(Player& player, Enemy& enemy, std::vector<std::string>& b)
{
    enemy.take_damage(1);
            if (!enemy.is_alive())
            {
                std::cout << "Potwór pokonany" << '\n';
                b[enemy.y][enemy.x] = '.';
            }
            else
            {
                player.take_damage(1);
                std::cout << "Potwór cię zaatakował!" << '\n';
                std::cout << "Zdrowie gracza: " << player.get_health() << '\n';
                std::cout << "Zdrowie potwora: " << enemy.get_health() << '\n';
            }
}

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

    void count_treasures()
    {
        treasures = 0;
        for (const std::string& row : board)
        {
            for (char field : row)
            {
                if (field == '$')
                    treasures++;
            }
        }
    }

    bool is_won() const
    {
        return treasures == 0;
    }

    bool is_lost() const
    {
        return !player.is_alive();
    }

    void run();

};

void Game::move_player(char direction)
{
    int dx = 0;
    int dy = 0;

    switch (direction)
{
    case 'w':
        dy = -1;
        break;

    case 'a':
        dx = -1;
        break;
    
    case 's':
        dy = 1;
        break;
    
    case 'd':
        dx = 1;
        break;

    default:
        std::cout << "Nieznany kierunek!" << '\n';
        return;
}
    int new_x = player.x + dx;
    int new_y = player.y + dy;

    if (new_y >= 0 && new_y < static_cast<int>(board.size()) && new_x >= 0  && new_x < static_cast<int>(board[new_y].size()) && board[new_y][new_x] != '#')
    {
        for (Enemy& enemy : enemies)
        {
            if (new_x == enemy.x && new_y == enemy.y && enemy.is_alive())
            {
                fight(player, enemy, board);
                return;
            }
        }


        if (board[new_y][new_x] == '$')
        {
            player.score += 10;
            treasures--;
        }
            
        board[player.y][player.x] = '.';
        board[new_y][new_x] = '@';
        player.x = new_x;
        player.y = new_y;
    }
    else
        std::cout << "Brak możliwości ruchu!" << '\n';
}

void Game::display_board() const
{
     for(const std::string& s : board){
        std::cout << s << '\n';
    }
}

void Game::display_status() const
{
    std::cout << "Twoja obecna ilosc punktów to: " << player.score << '\n';
    std::cout << "Pozostałe skarby: " << treasures << '\n';
    std::cout << "Życie: " << player.get_health() << '\n';
}

void Game::run()
{
    count_treasures();
    std::cout << "Liczba skarbów na planszy: " << treasures << std::endl;
    std::cout << "Witaj w Dungeon Explorer!" << std::endl;
    display_board();
    display_status();
    char direction;
    std:: cout << "Podaj kierunek (w/a/s/d), q - wyjście: ";
    while (std::cin >> direction){
        if (direction == 'q')
            break;
        move_player(direction);
        display_board();
        display_status();
        if (is_lost())
        {
            std::cout << "Przegrałeś!" << std::endl;
            break;
        }
        if (is_won())
        {
            std::cout << "Gratulacje! Zebrałeś wszystkie skarby!" << std::endl;
            std::cout << "Twój końcowy wynik: " << player.score << " punktów." <<  std::endl;
            break;
        }
        std:: cout << "Podaj kierunek (w/a/s/d), q - wyjście: ";
    }
}

int main()
{
    Game game;
    game.run();
   
    return 0;
}