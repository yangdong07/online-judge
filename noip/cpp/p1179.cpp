// P1179 数字统计
// https://www.luogu.org/problemnew/show/P1179


#include <cstdio>

int main()
{
    int L, R, n;
    scanf("%d %d", &L, &R);

    int count = 0;
    for (int i = L; i <= R; ++i)
    {
        n = i;
        while (n) 
        {
            if (n % 10 == 2) count++;
            n /= 10;
        }
    }
    printf("%d", count);
}