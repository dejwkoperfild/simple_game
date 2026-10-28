#include <iostream>
#include <vector>
#include <string>

struct Player
{
    int x = 1;
    int y = 1;
    int score = 0;
    int health = 3;
};

struct Enemy
{
    int x;
    int y;
    int health;

    Enemy(int start_x, int start_y, int start_health)
    : x(start_x), y(start_y), health(start_health)
    {}

    void take_damage(int damage)
    {
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
                player.health--;
                std::cout << "Potwór cię zaatakował!" << '\n';
                std::cout << "Zdrowie gracza: " << player.health << '\n';
                std::cout << "Zdrowie potwora: " << enemy.get_health() << '\n';
            }
}

void move_player(std::vector<std::string>& b, Player& player, std::vector<Enemy>& enemies, char direction, int& treasures)
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

    if (new_y >= 0 && new_y < static_cast<int>(b.size()) && new_x >= 0  && new_x < static_cast<int>(b[new_y].size()) && b[new_y][new_x] != '#')
    {
        for(Enemy& enemy : enemies)
        {
            if (new_x == enemy.x && new_y == enemy.y && enemy.is_alive())
            {
                fight(player, enemy, b);
                return;
            }
        }


        if (b[new_y][new_x] == '$')
        {
            player.score += 10;
            treasures--;
        }
            
        b[player.y][player.x] = '.';
        b[new_y][new_x] = '@';
        player.x = new_x;
        player.y = new_y;
    }
    else
        std::cout << "Brak możliwości ruchu!" << '\n';
}

void display_board(const std::vector<std::string>& b)
{
     for(const std::string& s : b){
        std::cout << s << '\n';
    }
}

int main()
{
    Player player;
    std::vector<Enemy> enemies = {
    Enemy{5, 4, 2},
    Enemy{7, 2, 3}
    };
    std::cout << "Liczba punktów gracz: " << player.score << std::endl;
    std::cout << "Zdrowie gracza: " << player.health << std::endl;

    // zmienna przechowująca plansze
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

    int treasures = 0;
    for (const std::string& row : board)
    {
        for (char field : row)
        {
            if (field == '$')
                treasures++;
        }
    }
    std::cout << "Liczba skarbów na planszy: " << treasures << std::endl;
    std::cout << "Witaj w Dungeon Explorer!" << std::endl;

    // wyświetlenie planszy
    display_board(board);

    char direction;
    std:: cout << "Podaj kierunek (w/a/s/d), q - wyjście: ";
    while (std::cin >> direction){
        if (direction == 'q')
            break;
        move_player(board, player, enemies, direction, treasures);
        display_board(board);
        std::cout << "Twoja obecna ilosc punktów to: " << player.score << '\n';
        std::cout << "Pozostałe skarby: " << treasures << '\n';
        std::cout << "Życie: " << player.health << '\n';
        if (player.health <= 0)
        {
            std::cout << "Przegrałeś!" << std::endl;
            break;
        }
        if (treasures == 0)
        {
            std::cout << "Gratulacje! Zebrałeś wszystkie skarby!" << std::endl;
            std::cout << "Twój końcowy wynik: " << player.score << " punktów." <<  std::endl;
            break;
        }
        std:: cout << "Podaj kierunek (w/a/s/d), q - wyjście: ";
    }

   

   
    return 0;
}