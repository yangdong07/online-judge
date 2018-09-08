/*
    Minimum Spanning Tree - Prim algorithm

    在稠密图情形下，用 Prim 数组实现是比较好的方法。并且常数因子比较小。
    P2872 评测是 99ms，同样的Kruskal 算法是 500ms。
*/

#include <cstdio>
#include <queue>
#include <cmath>

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
    double min_cost = 0;

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
        min_cost += min_w;

        for (j = 1; j <= n; ++j)
            if (!visit[j] && weight[j] > cost[i][j])
                weight[j] = cost[i][j];
    }
    return min_cost;
}


int main()
{
    int n, k, i, j;

    scanf("%d %d", &n, &k);

    Point *points = (Point *)malloc((n + 1) * sizeof(Point));
    for (i = 1; i <= n; ++i)
        scanf("%d %d", &points[i].x, &points[i].y);

    for (i = 1; i <= n; ++i)
        for (j = i; j <= n; ++j)
            cost[i][j] = cost[j][i] = points[i].d(points[j]);

    while (k--)
    {
        scanf("%d %d", &i, &j);
        cost[i][j] = cost[j][i] = 0.0;
    }

    double min_cost = mst_prim(1, n);
    printf("%.2lf\n", min_cost);
    return 0;
}

