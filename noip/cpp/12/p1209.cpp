
// P1209 [USACO1.3]修理牛棚 Barn Repair
// https://www.luogu.org/problemnew/show/P1209

#include <cstdio>
#include <algorithm>

int main()
{
    const int MAX_N = 201;
    int m, s, c;
    scanf("%d%d%d", &m, &s, &c);


    int stalls[MAX_N] = {0}, id;
    for (int i = 0; i < c; ++i)
    {
        scanf("%d", &id);
        stalls[id] = 1;
    }

    int l = 1, r = s;
    // trim 0s
    while (stalls[l] == 0) ++l;
    while (stalls[r] == 0) --r;

    int total = r - l + 1;
    // trim 1s
    while (stalls[l] == 1) ++l;

    int nonblocked[MAX_N] = {0};
    int count = 0, n = 0;
    for (int i = l; i <= r; ++i)
    {
        if (stalls[i] == 0)
            count++;
        else
        {
            nonblocked[n++] = count;
            count = 0;
        }
    }

    std::sort(nonblocked, nonblocked + n);

    int acc = 0, limit = std::max(n - m + 1, 0);
    for (int i = n - 1; i >= limit; --i)
        acc += nonblocked[i];
    
    printf("%d\n", total - acc);

    return 0;
}