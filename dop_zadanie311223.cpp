#include <iostream>
#include <vector>
#include <algorithm>


std::vector<std::vector<int>> createGrid(int rows, int cols) {
    std::vector<std::vector<int>> grid(rows, std::vector<int>(cols, 0));
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            grid[i][j] = rand() % 2;
        }
    }
    return grid;
}


void printGrid(const std::vector<std::vector<int>>& grid, int i) {
    for (const auto& row : grid) {
        for (int cell : row) {
            std::cout << (cell == 1 ? '*' : ' ') << ' ';
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    for (int j = 0; j < i * 2; j++)
    {
        std::cout << "-";
    }
    std::cout << std::endl;
}

int check(int i, int j, const std::vector<std::vector<int>>& grid)
{
    if (grid[i][j] == 1) return 1;
    else return 0;
}

std::vector<std::vector<int>> evolve(int rows, int cols, const std::vector<std::vector<int>>& grid)
{
    std::vector<std::vector<int>> gen(rows, std::vector<int>(cols, 0));
    std::vector<std::vector<int>> ngrid(rows, std::vector<int>(cols, 0));

    for (int i = 0; i < cols; i++)
    {
        for (int j = 0; j < rows; j++)
        {
            if (grid[i][j] == 1)
            {
                if (i == 0 && j == 0)
                {
                    gen[0][1]++;
                    gen[1][1]++;
                    gen[1][0]++;
                }
                else if (i == 0 && j == rows - 1)
                {
                    gen[0][rows - 2]++;
                    gen[1][rows - 2]++;
                    gen[1][rows - 1]++;
                }
                else if (i == cols - 1 && j == 0)
                {
                    gen[cols - 2][0]++;
                    gen[cols - 2][1]++;
                    gen[cols - 1][1]++;
                }
                else if (i == cols - 1 && j == rows - 1)
                {
                    gen[cols - 2][rows - 1]++;
                    gen[cols - 2][rows - 2]++;
                    gen[cols - 1][rows - 2]++;
                }
                else if (i == 0)
                {
                    gen[i][j - 1]++;
                    gen[i][j + 1]++;
                    gen[i + 1][j - 1]++;
                    gen[i + 1][j]++;
                    gen[i + 1][j + 1]++;
                }
                else if (j == 0)
                {
                    gen[i - 1][j]++;
                    gen[i + 1][j]++;
                    gen[i - 1][j + 1]++;
                    gen[i][j + 1]++;
                    gen[i + 1][j + 1]++;
                }
                else if (i == cols - 1)
                {
                    gen[i][j - 1]++;
                    gen[i][j + 1]++;
                    gen[i - 1][j - 1]++;
                    gen[i - 1][j]++;
                    gen[i - 1][j + 1]++;
                }
                else if (j == rows - 1)
                {
                    gen[i - 1][j]++;
                    gen[i + 1][j]++;
                    gen[i - 1][j - 1]++;
                    gen[i][j - 1]++;
                    gen[i + 1][j - 1]++;
                }
                else
                {
                    gen[i - 1][j - 1]++;
                    gen[i - 1][j]++;
                    gen[i - 1][j + 1]++;
                    gen[i][j - 1]++;
                    gen[i][j + 1]++;
                    gen[i + 1][j - 1]++;
                    gen[i + 1][j]++;
                    gen[i + 1][j + 1]++;
                }

            }
        }

    }
    for (int i = 0; i < cols; i++)
    {
        for (int j = 0; j < rows; j++)
        {
            if (grid[i][j] == 1)
            {
                if (gen[i][j] == 2 || gen[i][j] == 3)
                {
                    ngrid[i][j] = 1;
                }

            }
            if (grid[i][j] == 0)
            {
                if (gen[i][j] == 3)
                {
                    ngrid[i][j] = 1;
                }
            }
        }
    }
    return ngrid;


}

bool exitOne(const std::vector<std::vector<int>>& grid)
{
    for (const auto& row : grid)
    {
        for (int cell : row)
        {
            if (cell == 1) return false;

        }
    }
    return true;
}

bool exitTwoThree(const std::vector<std::vector<int>>& grid1, const std::vector<std::vector<int>>& grid2, int cols, int rows)
{
    for (int i = 0; i < cols; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (grid1[i][j] != grid2[i][j]) return false;
        }
    }
    return true;
}

int main()
{
    int i, j;
    std::cin >> i >> j;
    std::vector<std::vector<int>> game = createGrid(i, j);
    printGrid(game, i);
    std::vector< std::vector<std::vector<int>>> history;
    history.push_back(game);
    while (true)
    {
        game = evolve(i, j, game);
        printGrid(game, i);

        if (exitOne(game)) break;

        else if (exitTwoThree(game, history[history.size() - 1], i, j)) break;

        for (int counter = 0; counter < history.size(); counter++)
        {
            if (exitTwoThree(game, history[counter], i, j)) break;
        }
        history.push_back(game);


    }

}