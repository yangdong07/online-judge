
// P1204 [USACO1.2]挤牛奶Milking Cows
// https://www.luogu.org/problemnew/show/P1204

#include <cstdio>
#include <algorithm>

using namespace std;

struct Range
{
    int left;
    int right;
};

bool cmp(Range &a, Range &b)
{
    return a.left < b.left;
}

int main()
{
    const int MAX_N = 5001;
    int n, i, j;
    Range range[MAX_N];
    scanf("%d", &n);
    for (i = 0; i < n; i++)
        scanf("%d %d", &range[i].left, &range[i].right);
    sort(range, range + n, cmp);

    for (i = 0, j = 1; j < n; j++)
    {
        // merge
        if (range[j].left <= range[i].right)
            range[i].right = max(range[i].right, range[j].right);
        else
        {
            i++;
            range[i].left = range[j].left;
            range[i].right = range[j].right;
        }
    }
    n = i + 1;
    int max0 = 0, max1 = range[0].right - range[0].left;
    for (i = 1; i < n; ++i)
    {
        // printf("%d %d\n", range[i].left, range[i].right);
        max0 = max(max0, range[i].left - range[i - 1].right);
        max1 = max(max1, range[i].right - range[i].left);
    }
    printf("%d %d\n", max1, max0);

    return 0;
}