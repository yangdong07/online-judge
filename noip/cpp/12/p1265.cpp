
// P1265 公路修建
// https://www.luogu.org/problemnew/show/P1265


#include <cstdio>
#include <cmath>
#include <algorithm>

using namespace std;

struct Point
{
    int x, y;
    double d(const Point &b) const
    {
        return (double)(x - b.x) * (x - b.x) + (double)(y - b.y) * (y - b.y);
    }
};

const int MAX_V = 5000;
double INF = 1e30;
Point points[MAX_V];

double mst_prim(int n)
{
    double min_cost = 0;
    int i, j, k;
    bool visit[MAX_V] = {false};
    double min_w, weight[MAX_V];

    weight[0] = 0;
    for (i = 1; i < n; ++i)
        weight[i] = INF;

    for (k = 0; k < n; ++k)
    {
        min_w = INF;
        i = 0;
        for (j = 0; j < n; ++j)
            if (!visit[j] && weight[j] < min_w)
                i = j, min_w = weight[j];
        visit[i] = true;
        min_cost += sqrt(min_w);

        for (j = 0; j < n; ++j)
            if (!visit[j])
                weight[j] = min(weight[j], points[i].d(points[j]));
    }
    return min_cost;
}


int main()
{
    int n, i;
    scanf("%d", &n);
    for (i = 0; i < n; ++i)
        scanf("%d %d", &points[i].x, &points[i].y);

    printf("%.2lf\n", mst_prim(n));
    return 0;
}
