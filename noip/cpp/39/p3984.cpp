
// P3984 高兴的津津
// https://www.luogu.org/problemnew/show/P3984


#include <cstdio>

int main()
{
    int n, t, i;
    scanf("%d %d", &n, &t);
    int start, acc = 0, last, tmp;

    scanf("%d", &start);
    last = start + t;
    for (i = 1; i < n; ++i)
    {
        scanf("%d", &tmp);
        if (tmp > last)
        {
            acc += (last - start);
            start = tmp;
        }
        last = tmp + t;
    }
    printf("%d\n", acc + last - start);
    return 0;
}