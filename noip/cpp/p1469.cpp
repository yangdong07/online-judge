// P1469 找筷子
// https://www.luogu.org/problemnew/show/P1469

#include <cstdio>

int main()
{
    int n, l, i;
    int chopsticks=0;  // record every length
    scanf("%d", &n);
    for (i = 0; i < n; ++i)
    {
        scanf("%d", &l);
        chopsticks ^= l;
    }
    printf("%d", chopsticks);
}