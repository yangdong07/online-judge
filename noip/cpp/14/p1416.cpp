
// P1416 攻击火星
// https://www.luogu.org/problemnew/show/P1416

#include <cstdio>

int main()
{
    int n;
    scanf("%d", &n);
    printf("%d\n", n > 2 ? n - 2 : 0);
    return 0;
}