// P1425 小鱼的游泳时间
// https://www.luogu.org/problemnew/show/P1425

#include <cstdio>

int main()
{
    int h1, m1, h2, m2;
    scanf("%d %d %d %d", &h1, &m1, &h2, &m2);
    int min = (h2 - h1) * 60 + m2 - m1;
    printf("%d %d", min / 60, min % 60);
}