// P1795 无穷的序列_NOI导刊2010提高（05）
// https://www.luogu.org/problemnew/show/P1795

#include <cstdio>
#include <cmath>

using namespace std;

int main()
{
    int t, n, k;
    scanf("%d", &t);

    while (t--)
    {
        scanf("%d", &n);
        --n;
        n *= 2;
        k = int(sqrt(n - 0.25) + 0.5);
        putchar(k * (k + 1) == n ? '1' : '0');
        putchar('\n');
    }
}