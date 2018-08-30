// P2356 弹珠游戏
// https://www.luogu.org/problemnew/show/P2356

#include <cstdio>

#define MAX_N 1001

int main()
{
    int n, i, j;
    int num;
    int M[MAX_N][MAX_N] = { 0 };
    int row[MAX_N] = { 0 };
    int column[MAX_N] = { 0 };

    scanf("%d", &n);

    for (i = 0; i < n; ++i)
        for (j = 0; j < n; ++j)
        {
            scanf("%d", &num);
            row[i] += num;
            column[j] += num;
            M[i][j] = num;
        }

    int score = -1;
    for (i = 0; i < n; ++i)
        for (j = 0; j < n; ++j)
        {
            if (M[i][j] == 0 && score < row[i] + column[j])
                score = row[i] + column[j];
        }
    if (score == -1)
        printf("Bad Game!");
    else
        printf("%d", score);
}