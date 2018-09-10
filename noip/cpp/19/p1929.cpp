
// P1929 迷之阶梯
// https://www.luogu.org/problemnew/show/P1929

#include <cstdio>
#include <algorithm>

using namespace std;

typedef long long INT64;

int main()
{
    const int MAX_N = 201;
    const int MAX_STEP = 0x3f3f3f3f; 
    const INT64 INF = 1L << 33;
    int n, i, j, k, step[MAX_N];
    INT64 height[MAX_N];

    scanf("%d %lld", &n, &height[0]);
    step[0] = 0;

    int min_step;
    for (i = 1; i < n; ++i)
    {
        scanf("%lld", &height[i]);
        min_step = MAX_STEP;
        for (j = i - 1; j >= 0; --j)
            for (k = 0; k <= j && (1L << k) < INF; ++k)
                if (height[j - k] + (1L << k) >= height[i])
                    min_step = min(min_step, step[j] + k + 1);
        if (min_step == MAX_STEP)
        {
            printf("-1\n");
            return 0;
        }
        step[i] = min_step;
    }
    printf("%d\n", step[n - 1]);
    return 0;
}