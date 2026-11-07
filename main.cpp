#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>


struct Player
{
    int x = 1;
    int y = 1;
    int score = 0;
    

    void take_damage(int damage)
    {
        if (damage < 0)
            throw std::invalid_argument("Obrażenia nie mogą być ujemne!");
        
        this->health -=damage;
        if(this->health < 0)
            this->health = 0;
    }

    bool is_alive() const {return this->health>0;}
    int get_health() const {return this->health;}

    private:
        int health = 3;
};

struct Enemy
{
    int x;
    int y;

    private:
    int health;

    public:

    Enemy(int start_x, int start_y, int start_health)
    : x(start_x), y(start_y), health(start_health)
    {
        if (start_health < 0)
            throw std::invalid_argument("Zdrowie nie może być ujemne!");
    }

    void take_damage(int damage)
    {
        if (damage < 0)
            throw std::invalid_argument("Obrażenia nie mogą być ujemne!");
        
        this->health -=damage;
        if(this->health < 0)
            this->health = 0;
    }

    bool is_alive() const
{
    return this->health>0;
}

    int get_health() const
    {
        return this->health;
    }
};

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

int main()
{
    Game game;
    std::cout << "Liczba punktów gracz: " << game.player.score << std::endl;
    std::cout << "Zdrowie gracza: " << game.player.get_health() << std::endl;
    game.count_treasures();
    std::cout << "Liczba skarbów na planszy: " << game.treasures << std::endl;
    std::cout << "Witaj w Dungeon Explorer!" << std::endl;

    // wyświetlenie planszy
    game.display_board();

    char direction;
    std:: cout << "Podaj kierunek (w/a/s/d), q - wyjście: ";
    while (std::cin >> direction){
        if (direction == 'q')
            break;
        game.move_player(direction);
        game.display_board();
        std::cout << "Twoja obecna ilosc punktów to: " << game.player.score << '\n';
        std::cout << "Pozostałe skarby: " << game.treasures << '\n';
        std::cout << "Życie: " << game.player.get_health() << '\n';
        if (game.is_lost())
        {
            std::cout << "Przegrałeś!" << std::endl;
            break;
        }
        if (game.is_won())
        {
            std::cout << "Gratulacje! Zebrałeś wszystkie skarby!" << std::endl;
            std::cout << "Twój końcowy wynik: " << game.player.score << " punktów." <<  std::endl;
            break;
        }
        std:: cout << "Podaj kierunek (w/a/s/d), q - wyjście: ";
    }

   

   
    return 0;
}