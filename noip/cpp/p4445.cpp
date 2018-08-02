// P4445 [AHOI2018初中组]报名签到
// https://www.luogu.org/problemnew/show/P4445

#include <cstdio>
#include <algorithm>

using namespace std;

#define MAX_N 100000

int main()
{
    int n, i, d[MAX_N];
    scanf("%d", &n);
    for (i = 0; i < n; ++i)
        scanf("%d", &d[i]);

    long long dd = 0;
    for (i = 1; i < n; ++i)
        dd += max(d[i - 1], d[i]);
    printf("%lld", dd);
}