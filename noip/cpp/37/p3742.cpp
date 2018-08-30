// P3742 umi的函数
// https://www.luogu.org/problemnew/show/P3742

#include <cstdio>

#define MAX_N 101

int main()
{
    int n;
    char x[MAX_N], y[MAX_N];
    scanf("%d", &n);
    scanf("%s", x);
    scanf("%s", y);

    for (int i = 0; i < n; ++i)
    {
        if (x[i] < y[i]) {
            printf("-1");
            return 0;
        }
    }
    printf("%s", y);
}