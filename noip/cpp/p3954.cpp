// P3954 成绩
// https://www.luogu.org/problemnew/show/P3954

#include <cstdio>

int main()
{
    int a, b, c;
    scanf("%d %d %d", &a, &b, &c);

    printf("%d", (a * 20 + b * 30 + c * 50) / 100);
}