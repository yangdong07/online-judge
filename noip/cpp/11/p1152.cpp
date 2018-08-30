// P1152 欢乐的跳
// https://www.luogu.org/problemnew/show/P1152

#include <cstdio>
#include <algorithm>

using namespace std;

#define MAX_N 1000

int main()
{
    int n, p, c, d;
    bool visit[MAX_N];
    scanf("%d %d", &n, &p);
    for (int i = 1; i < n; ++i)
    {
        scanf("%d", &c);
        d = abs(p - c);
        if (d < n) visit[d] = true;
        p = c;
    }
    for (int i = 1; i < n; ++i)
        if (!visit[i]) {
            printf("Not jolly");
            return 0;
        }
    printf("Jolly");
}