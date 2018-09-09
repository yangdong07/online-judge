
// P2504 [HAOI2006]聪明的猴子
// https://www.luogu.org/problemnew/show/P2504

#include <cstdio>
#include <queue>
#include <cmath>
#include <algorithm>

using namespace std;

const int MAX_V = 1001;
double INF = 1e20;
double cost[MAX_V][MAX_V];

struct Point
{
    int x, y;
    double d(const Point &b) const
    {
        return sqrt((double)(x - b.x) * (x - b.x) + (double)(y - b.y) * (y - b.y));
    }
};

// Minimum Spanning Tree start from root, return minimum cost
double mst_prim(int root, int n)
{
    double max_d = 0;

    int i, j, k;
    bool visit[MAX_V] = {false};
    double min_w, weight[MAX_V];
    for (i = 1; i <= n; ++i)
        weight[i] = INF;

    weight[root] = 0.0;

    for (k = 0; k < n; ++k)
    {
        min_w = INF;
        i = 0;
        for (j = 1; j <= n; ++j)
            if (!visit[j] && weight[j] < min_w)
                i = j, min_w = weight[j];
        visit[i] = true;
        // if (min_w == INF) return min_cost;  // 
        max_d = max(max_d, min_w);

        for (j = 1; j <= n; ++j)
            if (!visit[j] && weight[j] > cost[i][j])
                weight[j] = cost[i][j];
    }
    return max_d;
}


int main()
{
    int m, n, i, j;

    const int MAX_M = 500;
    int jump[MAX_M];
    scanf("%d", &m);
    for (i = 0; i < m; ++i)
        scanf("%d", &jump[i]);
    
    scanf("%d", &n);

    Point *points = (Point *)malloc((n + 1) * sizeof(Point));
    for (i = 1; i <= n; ++i)
        scanf("%d %d", &points[i].x, &points[i].y);

    for (i = 1; i <= n; ++i)
        for (j = i; j <= n; ++j)
            cost[i][j] = cost[j][i] = points[i].d(points[j]);

    double max_d = mst_prim(1, n);

    int cnt = 0;
    for (i = 0; i < m; ++i)
        if (jump[i] >= max_d) cnt++;
    printf("%d\n", cnt);
    return 0;
}

