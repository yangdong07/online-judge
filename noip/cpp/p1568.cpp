// P1568 赛跑
// https://www.luogu.org/problemnew/show/P1568

#include <cstdio>
#include <algorithm>

using namespace std;

#define MAX_N 1001

int main()
{
    int m, n;
    int i, j;  // track step

    int s1[MAX_N], s2[MAX_N];  // speed
    int t1[MAX_N], t2[MAX_N];  // time interval

    scanf("%d %d", &n, &m);
    for (i = 1; i <= n; i++)
        scanf("%d %d", &s1[i], &t1[i]);
    for (i = 1; i <= m; i++)
    {
        scanf("%d %d", &s2[i], &t2[i]);
    }

    int t;  // min time interval
    int d1 = 0, d2 = 0;
    int state = -1, change = -1;
    for (i = 1, j = 1; i <= n && j <= m; )
    {
        t = min(t1[i], t2[j]);

        d1 += s1[i] * t;
        d2 += s2[j] * t;

        if (d1 != d2 && (d1 > d2) != state)
        {
            state = (d1 > d2);
            change++;
        }

        t1[i] -= t;
        t2[j] -= t;
        
        if (t1[i] == 0) ++i;
        if (t2[j] == 0) ++j;
    }
    if (change == -1) change = 0;
    printf("%d", change);
}