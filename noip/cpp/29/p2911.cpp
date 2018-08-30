// P2911 [USACO08OCT]牛骨头Bovine Bones
// https://www.luogu.org/problemnew/show/P2911

#include <cstdio>

#define MAX_N 100

int main()
{
    int s1, s2, s3;
    int i, j, k;
    int count[MAX_N] = { 0 };
    scanf("%d %d %d", &s1, &s2, &s3);

    int n = s1 + s2 + s3;

    for (i = 1; i <= s1; ++i)
        for (j = 1; j <= s2; ++j)
            for (k = 1; k <= s3; ++k)
                count[i + j + k]++;
    
    for (i = 3; i < n; ++i)
    {
        if (count[i] >= count[i + 1])
        {
            printf("%d", i);
            break;
        }
    }
}