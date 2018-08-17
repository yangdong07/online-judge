#include <cstdio>

#define N 9
#define NN 81

int grid[NN];
bool row[N][N + 1], col[N][N + 1], box[N][N + 1];
bool flag = false;  // found result

void print_grid()
{
    for (int i = 0; i < 9; i++, putchar('\n'))
        for (int j = 0; j < 9; j++)
            printf("%d ", grid[i * N + j]);
}

void search(int k)
{
    while (k < NN && grid[k] != 0) ++k;
    if (k == NN)
    {
        flag = true;
        print_grid();
        return;
    }

    int r = k / N, c = k % N;
    for (int i = 1; i <= 9; i++)
        if (!row[r][i] && !col[c][i] && !box[r / 3 * 3 + c / 3][i])
        {
            row[r][i] = col[c][i] = box[r / 3 * 3 + c / 3][i] = 1;
            grid[k] = i;
            search(k + 1);
            if (flag) return;
            row[r][i] = col[c][i] = box[r / 3 * 3 + c / 3][i] = 0;
            grid[k] = 0;
        }
}

int main()
{
    int i, j, t;
    for (i = 0; i < N; i++)
        for (j = 0; j < N; j++)
        {
            scanf("%d", &t);
            grid[i * N + j] = t;
            if (t)
                row[i][t] = col[j][t] = box[i / 3 * 3 + j / 3][t] = 1;
        }
    search(0);
    return 0;
}
