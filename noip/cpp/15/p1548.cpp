// P1548 棋盘问题
// https://www.luogu.org/problemnew/show/P1548

#include <cstdio>


int main()
{
    int n, m;
    scanf("%d %d", &n, &m);

    int quadrangle = (n + 1) * (m + 1) * n * m / 4;
    int square = 0;
    for (int i = n, j = m; i >= 1 && j >= 1; --i, --j) 
        square += i * j;

    printf("%d %d", square, quadrangle - square);
}