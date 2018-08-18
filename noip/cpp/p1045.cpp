// P1045 麦森数
// https://www.luogu.org/problemnew/show/P1045

#include <cstdio>
#include <cmath>
#include <cstring>

const int MAX_N = 500;

int tmp[MAX_N];

// b *= a;
void self_multiply(int b[], int a[])
{
    int i, j;

    memset(tmp, 0, sizeof(tmp));

    for (i = 0; i < MAX_N; ++i)   // a
        for (j = 0; i + j < MAX_N; ++j)   // b
            tmp[i + j] += a[i] * b[j];
    
    int carry = 0;
    for (i = 0; i < MAX_N; ++i)
    {
        carry += tmp[i];
        b[i] = carry % 10;
        carry /= 10;
    }
}

int main()
{
    int a[MAX_N], b[MAX_N];
    int p, t;
    scanf("%d", &p);

    memset(a, 0, sizeof(a));
    memset(b, 0, sizeof(b));
    a[0] = 2;
    b[0] = 1;

    printf("%d\n", (int)(log10(2) * p + 1));

    for (int t = p; t; t >>= 1)
    {
        if (t & 1)
            self_multiply(b, a);
        self_multiply(a, a);
    }

    --b[0];  // 这里可以直接减，因为 2的任何次幂最后一位都不可能是0， 不用借位
    for (int i = MAX_N - 1; i >= 0; --i)
    {
        printf("%d", b[i]);
        if (i % 50 == 0) printf("\n");
    }

    return 0;
}