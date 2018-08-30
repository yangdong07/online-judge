// P1426 小鱼会有危险吗
// https://www.luogu.org/problemnew/show/P1426

#include <cstdio>

int main()
{
    double s, x;
    scanf("%lf %lf", &s, &x);

    double distance = 0.0, velocity = 7.0;

    while (distance < s - x) {
        distance += velocity;
        velocity *= 0.98;
    }

    if (distance + velocity < s + x) printf("y");
    else printf("n");
}