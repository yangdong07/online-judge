
// P2212 [USACO14MAR]浇地Watering the Fields
// https://www.luogu.org/problemnew/show/P2212

#include <cstdio>
#include <queue>
#include <cmath>

using namespace std;

const int MAX_V = 2001;
const int INF = 1000 * 1000 * 2 + 1;
int cost[MAX_V][MAX_V];

struct Point
{
    int x, y;
    int d(const Point &b) const
    {
        return (x - b.x) * (x - b.x) + (y - b.y) * (y - b.y);
    }
};

// Minimum Spanning Tree start from root, return minimum cost
bool mst_prim(int root, int n, int &min_cost)
{
    min_cost = 0;

    int i, j, k;
    bool visit[MAX_V] = {false};
    int min_w, weight[MAX_V];
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
        if (min_w == INF) return false;
        min_cost += min_w;

        for (j = 1; j <= n; ++j)
            if (!visit[j] && weight[j] > cost[i][j])
                weight[j] = cost[i][j];
    }
    return true;
}


int main()
{
    int n, cut, i, j;

    scanf("%d %d", &n, &cut);

    Point *points = (Point *)malloc((n + 1) * sizeof(Point));
    for (i = 1; i <= n; ++i)
        scanf("%d %d", &points[i].x, &points[i].y);

    int weight;
    for (i = 1; i <= n; ++i)
        for (j = i; j <= n; ++j)
        {
            weight = points[i].d(points[j]);
            if (weight < cut)
                cost[i][j] = cost[j][i] = INF;
            else
                cost[i][j] = cost[j][i] = weight;
        }

    int min_cost;
    if (mst_prim(1, n, min_cost))
        printf("%d\n", min_cost);
    else
        printf("-1\n");
    return 0;
}

