// P1784 数独
// https://www.luogu.org/problemnew/show/P1784

#include <cstdio>
 
#define N 9
#define UNASSIGNED 0

// int g[N][N] = {{3, 0, 6, 5, 0, 8, 4, 0, 0},
//                {5, 2, 0, 0, 0, 0, 0, 0, 0},
//                {0, 8, 7, 0, 0, 0, 0, 3, 1},
//                {0, 0, 3, 0, 1, 0, 0, 8, 0},
//                {9, 0, 0, 8, 6, 3, 0, 0, 5},
//                {0, 5, 0, 0, 9, 0, 6, 0, 0},
//                {1, 3, 0, 0, 0, 0, 2, 5, 0},
//                {0, 0, 0, 0, 0, 0, 0, 7, 4},
//                {0, 0, 5, 2, 0, 6, 3, 0, 0}};
int g[N][N];

void print_solution()
{
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
            printf("%d ", g[i][j]);
        printf("\n");
    }
}

bool is_safe(int r, int c, int num)
{
    int i;
    // row
    for (i = 0; i < N; ++i)
        if (g[r][i] == num)
            return false;
    // col
    for (i = 0; i < N; ++i)
        if (g[i][c] == num)
            return false;
    // box
    r -= r % 3;
    c -= c % 3;
    for (i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            if (g[r + i][c + i] == num)
                return false;
    return true;
}

bool find_unassigned(int &r, int &c)
{
    for (r = 0; r < N; r++)
        for (c = 0; c < N; c++)
            if (g[r][c] == UNASSIGNED)
                return true;
    return false;
}
 
bool solve_sudoku()
{
    int row, col;
    if (!find_unassigned(row, col))
    {
        print_solution();
        return true;
    }
    // consider digits 1 to 9
    for (int num = 1; num <= 9; num++)
    {
        if (is_safe(row, col, num))
        {
            g[row][col] = num;
            solve_sudoku();
            // if (solve_sudoku()) return true;
            g[row][col] = UNASSIGNED;
        }
    }
    return false;
}


int main()
{
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            scanf("%d", &g[i][j]);

    solve_sudoku();
 
    return 0;
}