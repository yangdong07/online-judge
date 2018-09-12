
// P2723 丑数 Humble Numbers
// https://www.luogu.org/problemnew/show/P2723
#include <cstdio>
#include <algorithm>

using namespace std;

const int MAX_M = 100;
const int MAX_N = 100000 + 1;
const int INF = 0x7fffffff;

int humbles[MAX_N];
int primes[MAX_M];


int find_humble(int i, int prime)
{
    int l = 0, r = i - 1, m;
    int bound = humbles[r] / prime;

    while (l < r)
    {
        m = (l + r) / 2;
        if (humbles[m] <= bound)
            l = m + 1;
        else
            r = m;
    }
    return humbles[l] * prime;
}

int main()
{
    int m, n, i, j;
    scanf("%d %d", &m, &n);
    
    for (i = 0; i < m; ++i)
        scanf("%d", &primes[i]);
    
    humbles[0] = 1;
    humbles[1] = primes[0];

    int min_h;
    for (i = 2; i <= n; ++i)
    {
        min_h = INF;
        for (j = 0; j < m; ++j)
            min_h = min(min_h, find_humble(i, primes[j]));
        humbles[i] = min_h;
    }

    printf("%d", humbles[n]);

    return 0;
}