
// P2731 骑马修栅栏 Riding the Fences
// https://www.luogu.org/problemnew/show/P2731

#include <cstdio>
#include <algorithm>
using namespace std;

const int MAX_N = 500 + 1;
const int MAX_M = 1024 + 1;

int n;
int adjs[MAX_N][MAX_N] = {0};
int circuit[MAX_M], ci = 0;

void hierholzer(int u)
{
    for (int v = 1; v <= n; v++)
        if (adjs[u][v])
        {
            adjs[u][v]--;
            adjs[v][u]--;
            hierholzer(v);
        }
    circuit[ci++] = u;
}

int main()
{
    int m, i, j, k;
    scanf("%d", &m);

    int degree[MAX_N] = {0};   // find start
    n = 0;
    for (k = 0; k < m; ++k)
    {
        scanf("%d %d", &i, &j);
        n = max(n, max(i, j));
        ++adjs[i][j];
        ++adjs[j][i];
        ++degree[i], ++degree[j];
    }
    // for (i = 1; i <= n; ++i)
    //     printf("%d ", degree[i]);
    // printf("\n");

    for (i = 1; i <= n; ++i)
        if (degree[i] & 1) break;

    if (i == n + 1) // no vertex with odd degree
        for (i = 1; i <= n && !degree[i]; ++i);
    // printf("%d %d\n", n, i);

    hierholzer(i);

    for (j = ci - 1; j >= 0; --j)
        printf("%d\n", circuit[j]);
    return 0;
}
