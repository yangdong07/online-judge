
// P2074 危险区域
// https://www.luogu.org/problemnew/show/P2074


#include <cstdio>
#include <algorithm>

using namespace std;

int main()
{
    int m, n, k, radius;
    scanf("%d%d%d%d", &n, &m, &k, &radius);

    int x, y, cx, cy, total;
    int max_d = 0;
    while (k--)
    {
        scanf("%d%d", &cx, &cy);
        total = 0;
        for (x = max(1, cx - radius); x <= min(n, cx + radius); x++)
            for (y = max(1, cy - radius); y <= min(m, cy + radius); y++)
                if ((x - cx) * (x - cx) + (y - cy) * (y - cy) <= radius * radius)
                    ++total;
        if (total > max_d)
            max_d = total;
    }
    printf("%d", max_d);
}