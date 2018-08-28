// P2983 [USACO10FEB]购买巧克力Chocolate Buying
// https://www.luogu.org/problemnew/show/P2983

#include <cstdio>
#include <algorithm>

#define MAX_N 100001

using namespace std;

typedef long long INT64;

INT64 p[MAX_N], c[MAX_N];

bool cmp(int i, int j)
{
    return p[i] < p[j];
}

INT64 read_num()
{
    char c;
    INT64 num = 0;
    for (c = getchar(); c < '0' || c > '9'; c = getchar());

    for (; c >= '0' && c <= '9'; c = getchar())
        num = num * 10 + c - '0';
    return num;
}

int main()
{
    int n, i;
    INT64 b;
    scanf("%d %lld", &n, &b);

    int k[MAX_N];
    for (i = 0; i < n; ++i)
    {
        k[i] = i;
        p[i] = read_num();
        c[i] = read_num();
        // scanf("%lld %lld", &p[i], &c[i]);
    }
    
    sort(k, k + n, cmp);

    INT64 rest = b, satisfy = 0, st;
    int j;
    for (i = 0; i < n; ++i)
    {
        j = k[i];
        st = min(rest / p[j], c[j]);
        if (!st) break;
        satisfy += st;
        rest -= st * p[j];
    }
    printf("%lld", satisfy);
    return 0;
}