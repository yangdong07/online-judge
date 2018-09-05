
// P1522 牛的旅行 Cow Tours
// https://www.luogu.org/problemnew/show/P1522

#include <cstdio>
#include <cmath>
#include <algorithm>

using namespace std;

struct Position
{
    int x, y;
    double distance(const Position &b)
    {
        return sqrt((x - b.x) * (x - b.x) + (y - b.y) * (y - b.y));
    }
};


int main()
{
    const int MAX_N = 150;
    const double INF = 1e20;
    int n, i, j, k;
    Position a[MAX_N];
    scanf("%d\n", &n);
    for (i = 0; i < n; ++i)
        scanf("%d %d\n", &a[i].x, &a[i].y);
    
    double dist[MAX_N][MAX_N];
    char s[MAX_N + 1];
    for (i = 0; i < n; ++i)
    {
        scanf("%s", s);
        for (j = 0; j < n; ++j)
        if (s[j] == '1' || i == j)
            dist[i][j] = a[i].distance(a[j]);
        else
            dist[i][j] = INF;
    }

    // Floyd-Warshall
    for (k = 0; k < n; ++k)
        for (i = 0; i < n; ++i)
            for (j = 0; j < n; ++j)
                if (dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j];

    // for (i = 0; i < n; ++i)
    // {
    //     for (j = 0; j < n; ++j)
    //         if (dist[i][j] == INF)
    //             printf("%-6s", "INF");
    //         else
    //             printf("%-6.1lf", dist[i][j]);
    //     printf("\n");
    // }

    double max_d[MAX_N];
    for (i = 0; i < n; ++i)
    {
        max_d[i] = 0.0;
        for (j = 0; j < n; ++j)
            if (dist[i][j] != INF)
                max_d[i] = max(max_d[i], dist[i][j]);
    }

    // for (i = 0; i < n; ++i)
    //     printf("%-6.1lf", diameter[i]);
    // printf("\n");

    double min_d = INF;
    for (i = 0; i < n; ++i)
        for (j = 0; j < n; ++j)
            if (dist[i][j] == INF)
                min_d = min(min_d, max_d[i] + a[i].distance(a[j]) + max_d[j]);
    
    for (i = 0; i < n; ++i)
        min_d = max(min_d, max_d[i]);

    printf("%.6f\n", min_d);

    return 0;
}