// P1488 肥猫的游戏
// https://www.luogu.org/problemnew/show/P1488

#include <cstdio>

bool isNeighbor(int a, int b, int n)
{
    return (a + 1) % n == b || (b + 1) % n == a;
}

bool isContinuous(int a, int b, int c, int n)
{
    return (isNeighbor(a, b, n) + isNeighbor(b, c, n) + isNeighbor(a, c, n)) == 2;
}

int main()
{
    int n, i;
    int a, b, c; // vertics of triangle
    scanf("%d", &n);
    scanf("%d %d %d", &a, &b, &c);


    if (isContinuous(a, b, c, n))
    {
        printf("JMcat Win");
        return 0;
    }
    if (n & 1) printf("PZ Win");
    else printf("JMcat Win");

}