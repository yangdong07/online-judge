// P1720 月落乌啼算钱
// https://www.luogu.org/problemnew/show/P1720

#include <cstdio>

int main()
{
    double f[50];
    f[0] = 0;
    f[1] = 1;
    f[2] = 1;

    int n, i;
    scanf("%d", &n);

    for (i = 3; i <= n; i++)
        f[i] = f[i - 1] + f[i - 2]; 
    printf("%0.2lf", f[n]);
    return 0;
}