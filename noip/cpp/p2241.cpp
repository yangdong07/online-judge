// P2241 统计方形（数据加强版）
// https://www.luogu.org/problemnew/show/P2241

#include <cstdio>

int main()
{
    long long n, m;
    scanf("%lld %lld", &n, &m);

    long long quadrangle = (n + 1) * (m + 1) * n * m / 4;
    long long square = 0;
    for (long long i = n, j = m; i >= 1 && j >= 1; --i, --j) 
        square += i * j;

    printf("%lld %lld", square, quadrangle - square);
}