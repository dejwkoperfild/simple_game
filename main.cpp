#include <iostream>
#include <vector>
#include <string>

void move_player(std::vector<std::string>& b, int& y, int& x, char direction, int& score)
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
        std::cout << "NIeznany kierunek!" << '\n';
        return;
}
    int new_x = x + dx;
    int new_y = y + dy;

    if (new_y >= 0 && new_y < static_cast<int>(b.size()) && new_x >= 0  && new_x < static_cast<int>(b[new_y].size()) && b[new_y][new_x] != '#')
    {
        if (b[new_y][new_x] == '$')
            score += 10;
        b[y][x] = '.';
        b[new_y][new_x] = '@';
        x = new_x;
        y = new_y;
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
    int score = 0;

    // zmienna przechowująca plansze
    std::vector<std::string> board = {
        "##########",
        "#@....$..#",
        "#........#",
        "#.$.##...#",
        "#........#",
        "#.....$..#",
        "#..$.....#",
        "##########",
    };

     std::cout << "Witaj w Dungeon Explorer!" << std::endl;

    // początkowe położenie gracza
    int y = 1; // wiersz
    int x = 1; // kolumna   

    // wyświetlenie planszy
    display_board(board);

    char direction;
    std:: cout << "Podaj kierunek (w/a/s/d), q - wyjście: ";
    while (std::cin >> direction){
        if (direction == 'q')
            break;
        move_player(board, y, x, direction, score);
        display_board(board);
        std::cout << "Twoja obecna ilosc punktów to: " << score << '\n';
        std:: cout << "Podaj kierunek (w/a/s/d), q - wyjście: ";
    }

   

   
    return 0;
}