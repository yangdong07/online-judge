// P1074 靶形数独
// https://www.luogu.org/problemnew/show/P1074

#include <cstdio>
#include <algorithm>

using namespace std;

#define N 9
#define NN 81

int grid[NN];
bool row[N][N + 1], col[N][N + 1], box[N][N + 1];
int score[NN];
int spiral[NN];

int max_sum = -1;

void print_grid()
{
    for (int i = 0; i < 9; i++, putchar('\n'))
    {
        for (int j = 0; j < 9; j++)
            printf("%d ", grid[i * N + j]);
    }
}

void search(int k, int sum)
{
    while (k < NN && grid[spiral[k]] != 0) ++k;
    if (k == NN)
    {
        if (sum > max_sum)
        {
            max_sum = sum;
            print_grid();
            printf("%d\n", max_sum);
        }
        // max_sum = sum;
        return;
    }

    int kk = spiral[k];
    int r = kk / N, c = kk % N;
    for (int i = 1; i <= 9; ++i)
        if (!row[r][i] && !col[c][i] && !box[r / 3 * 3 + c / 3][i])
        {
            row[r][i] = col[c][i] = box[r / 3 * 3 + c / 3][i] = 1;
            grid[kk] = i;
            search(k + 1, sum + i * score[kk]);
            // if (max_sum != -1) return;
            row[r][i] = col[c][i] = box[r / 3 * 3 + c / 3][i] = 0;
            grid[kk] = 0;
        }
}

int main()
{
    int i, j, t;
    int sum = 0;

    int raw_score[] = {6, 7, 8, 9, 10};
    for (i = 0; i < N; i++)
        for (j = 0; j < N; j++)
        {
            scanf("%d", &t);
            grid[i * N + j] = t;
            score[i * N + j] = raw_score[min(min(i, N - 1 - i), min(j, N - 1 - j))];
            if (t)
            {
                sum += t * score[i * N + j];
                row[i][t] = col[j][t] = box[i / 3 * 3 + j / 3][t] = 1;
            }
        }

    // spiral
    int rs = 0, re = N - 1, cs = 0, ce = N - 1;
    int k = 0;
    while (rs <= re && cs <= ce)
    {
        i = rs;
        for (j = cs; j < ce; ++j)
            spiral[k++] = i * N + j;
        for (; i < re; ++i)
            spiral[k++] = i * N + j;
        for (; j > cs; --j)
            spiral[k++] = i * N + j;
        for (; i > rs; --i)
            spiral[k++] = i * N + j;
        ++rs, ++cs, --re, --ce;
    }
    if (k < NN) spiral[k] = i * N + j;

    // for (i = 0; i < NN; ++i)
    //     printf("%d ", spiral[i]);
    // printf("\n");
    // for (i = 0; i < N; ++i, putchar('\n'))
    //     for(j = 0; j < N; ++j)
    //         printf("%3d", i * N + j);
    // printf("\n");
    search(0, sum);
    printf("%d\n", max_sum);
    return 0;
}