#include <iostream>
#include <vector>
#include <string>

void move_up(std::vector<std::string>& b, int& y, int x)
{
    if (y > 0 && b[y-1][x] != '#')
    {
        b[y][x] = '.';
        y--;
        b[y][x] = '@';
    }
    else
    {
        std::cout << "Nie możesz wejść w ściane!" << std::endl;
    }  
}

void move_down(std::vector<std::string>& b, int& y, int x)
{
    if (y + 1 < b.size() && b[y+1][x] != '#')
    {
        b[y][x] = '.';
        y++;
        b[y][x] = '@';
    }
    else
    {
        std::cout << "Nie możesz wejść w ściane!" << std::endl;
    }  
}

void move_right(std::vector<std::string>& b, int y, int& x)
{
    if (x + 1 < b[y].size() && b[y][x + 1] != '#')
        {
            b[y][x] = '.';
            x++;
            b[y][x] = '@';
        }
    else
    {
        std::cout << "Nie możesz wejść w ściane!" << std::endl;
    }   
}

void move_left(std::vector<std::string>& b, int y, int& x)
{
    if (x - 1 >= 0 && b[y][x - 1] != '#')
        {
            b[y][x] = '.';
            x--;
            b[y][x] = '@';
        }
    else
    {
        std::cout << "Nie możesz wejść w ściane!" << std::endl;
    }   
}

int main()
{
    // zmienna przechowująca plansze
    std::vector<std::string> board = {
        "##########",
        "#@.......#",
        "#........#",
        "#...##...#",
        "#........#",
        "#........#",
        "#........#",
        "##########",
    };

    // początkowe położenie gracza
    int y = 1; // kolumna
    int x = 1; // wiersz

    // przesunięcie gracza w prawo
    
    move_right(board, y, x);
    move_left(board, y, x);
    move_down(board, y, x);
    move_up(board, y, x);

    

    // wyświetlenie planszy
    for(const std::string& s : board){
        std::cout << s << '\n';
    }
   

    std::cout << "Witaj w Dungeon Explorer!" << std::endl;

    return 0;
}