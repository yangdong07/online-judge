// P1534 不高兴的津津（升级版）
// https://www.luogu.org/problemnew/show/P1534

#include <cstdio>

int main()
{
    int n, i;
    scanf("%d", &n);
    int meitounao, bugaoxing, unhappy = 0, sum = 0;
    for (i = 0; i < n; ++i)
    {
        scanf("%d %d", &meitounao, &bugaoxing);
        unhappy += (meitounao + bugaoxing - 8);
        sum += unhappy;
    }
    printf("%d", sum);
}