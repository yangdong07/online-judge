
// P1459 三值的排序 Sorting a Three-Valued Sequence
// https://www.luogu.org/problemnew/show/P1459

#include <cstdio>

int min(int a, int b) { return a < b ? a : b; }

int main()
{
    const int MAX_N = 1001;
    int n, i, j;

    scanf("%d", &n);
    
    int a[MAX_N], b[MAX_N];
    int mismatch[4][4] = {0};
    int count[4] = {0};
    for (i = 0; i < n; ++i)
    {
        scanf("%d", &a[i]);
        count[a[i]]++;
    }
    j = 0;
    for (int k = 1; k <= 3; ++k)
        for (i = 0; i < count[k]; ++i)
            b[j++] = k;
    
    // for (i = 0; i < n; ++i)
    //     printf("%d ", a[i]);
    // printf("\n");
    // for (i = 0; i < n; ++i)
    //     printf("%d ", b[i]);
    // printf("\n");

    for (i = 0; i < n; ++i)
        mismatch[b[i]][a[i]]++;

    int swap = 0, sx, rest = 0;
    for (i = 1; i <= 3; ++i)
    {
        for (j = i + 1; j <= 3; ++j)
        {
            sx = min(mismatch[i][j], mismatch[j][i]); 
            swap += sx;
            mismatch[i][j] -= sx;
            mismatch[j][i] -= sx;
            rest += (mismatch[i][j] + mismatch[j][i]);
        }
    }
    printf("%d\n", swap + rest * 2 / 3);

    return 0;
}