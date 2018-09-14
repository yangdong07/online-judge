
// P1927 防护伞
// https://www.luogu.org/problemnew/show/P1927

#include <cstdio>
#include <algorithm>

using namespace std;

struct Point
{
    int x, y;
    int d(const Point &b) const
    {
        return (x - b.x) * (x - b.x) + (y - b.y) * (y - b.y);
    }
};

int main()
{
    const int MAX_N = 1000;
    const int INF = 0x7fffffff;
    const double PI = 3.1415926535;
    int n, i, j;
    Point points[MAX_N];
    int dist[MAX_N][MAX_N] = {0};

    scanf("%d", &n);
    for (i = 0; i < n; ++i)
        scanf("%d %d", &points[i].x, &points[i].y);
    
    for (i = 0; i < n; ++i)
        for (j = i + 1; j < n; ++j)
            dist[i][j] = dist[j][i] = points[i].d(points[j]);
    
    int max_d = 0, min_d = INF;
    for (i = 0; i < n; ++i)
    {
        max_d = 0;
        for (j = 0; j < n; ++j)
            max_d = max(max_d, dist[i][j]);
        min_d = min(min_d, max_d);
    }
    printf("%.4lf", PI * min_d);

    return 0;
}