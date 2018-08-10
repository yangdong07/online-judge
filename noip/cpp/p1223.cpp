// P1223 排队接水
// https://www.luogu.org/problemnew/show/P1223

#include <cstdio> 
#include <algorithm>

using namespace std;

#define MAX_N 1001

typedef pair<int, int> vip;

bool cmp(const vip &a, const vip &b)
{
    return a.first < b.first;
}

int main()
{
    int n, i, t;
    scanf("%d", &n);

    vip vi[MAX_N];
    for (i = 1; i <= n; ++i)
    {
        scanf("%d", &t);
        vi[i] = make_pair(t, i);
    }
    sort(vi + 1, vi + n + 1, cmp);

    long long wait_time = 0;
    for (i = 1; i <= n; ++i)
    {
        printf("%d ", vi[i].second);
        wait_time += vi[i].first * (n - i);
    }
    printf("\n%.2f", 1.0 * wait_time / n);

    return 0; 
}