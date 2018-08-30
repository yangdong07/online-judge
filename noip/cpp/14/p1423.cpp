// P1423 小玉在游泳
// https://www.luogu.org/problemnew/show/P1423

#include <cstdio>

int main()
{
    double distance;
    scanf("%lf", &distance);

    int step = 0;
    double swim = 2.0;
    while (distance > 0)
    {
        step++;
        distance -= swim;
        swim *= 0.98;
    }
    printf("%d", step);
}