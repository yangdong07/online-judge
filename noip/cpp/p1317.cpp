// P1317 低洼地
// https://www.luogu.org/problemnew/show/P1317

#include <cstdio>

#define MAX_N 10000

int main()
{
    int n, i, heights[MAX_N];
    scanf("%d", &n);
    for (i = 0; i < n; ++i)
        scanf("%d", &heights[i]);
    
    int count = 0, ii = 2;
    // de-duplicate first
    for (i = 3; i < n - 1; ++i) {
        if (heights[i] != heights[ii])
            heights[++ii] = heights[i];
    }
    // check and count
    for (i = 2; i < ii; ++i)
        if (heights[i] < heights[i - 1] && heights[i] < heights[i + 1])
            count++;
    printf("%d", count);
}