// P1567 统计天数
// https://www.luogu.org/problemnew/show/P1567

#include <cstdio>
#include <algorithm>

using namespace std;

int main()
{
    int n, i;
    scanf("%d", &n);
    int t0 = -1, t;
    int count = 0, maxCount = 0;
    for (i = 0; i < n; ++i)
    {
        scanf("%d", &t);
        if (t <= t0)
        {
            maxCount = max(count, maxCount);
            count = 0;
        }
        count++;
        t0 = t;
    }
    maxCount = max(count, maxCount);
    printf("%d", maxCount);
}