// P2807 三角形计数
// https://www.luogu.org/problemnew/show/P2807

#include <cstdio>

const int MAX_N = 501;

int main()
{
    int a[MAX_N], i;
    a[0] = 0;
    a[1] = 1;
    a[2] = 5;

    for (i = 3; i < MAX_N; ++i)
        a[i] = 1 + 3 * a[i - 1] - 3 * a[i - 2] + 2 * a[i - 3];
    
    for (i = 0; i < 13; ++i)
        printf("%d ", a[i]);

    return 0;
}