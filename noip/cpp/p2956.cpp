// P2956 [USACO09OCT]机器人犁田The Robot Plow
// https://www.luogu.org/problemnew/show/P2956

#include <cstdio>

#define MAX_N 241

int main()
{
    int x, y, l;
    int i, j, k;
    int quard[MAX_N][MAX_N] = { 0 };
    int xll, yll;  // stand for lower left
    int xur, yur;  // stand for upper right
    scanf("%d %d %d", &x, &y, &l);
    for (k = 0; k < l; ++k)
    {
        scanf("%d %d %d %d", &xll, &yll, &xur, &yur);
        for (i = xll; i <= xur; ++i)
            for (j = yll; j <= yur; ++j)
                if (i > 0 && i <= x && j > 0 && j <= y)
                    quard[i][j] = 1;
    }

    int count = 0;
    for (i = 1; i <= x; ++i)
        for (j = 1; j <= y; ++j)
            count += quard[i][j];
    printf("%d", count);
}