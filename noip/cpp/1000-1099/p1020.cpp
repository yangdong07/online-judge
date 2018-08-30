// P1020 导弹拦截
// https://www.luogu.org/problemnew/show/P1020

#include <cstdio>

bool less(int a, int b) { return a < b; }

bool noless(int a, int b) { return a >= b; }

void find_replace(int s[], int n, int x,
                 bool (*cmp)(int, int))
{
    int l = 0, r = n - 1, m;
    while (l < r)
    {
        m = (l + r) / 2;
        if (cmp(s[m], x))
            l = m + 1;
        else
            r = m;
    }
    s[l] = x;
}

int main()
{
    const int MAX_N = 100001;
    int a[MAX_N], n = 0;
    while (scanf("%d", &a[n]) != EOF) ++n;
    // for (int i = 0; i < n; ++i)
    //     printf("%d ", a[i]);

    int s[MAX_N], i, j, l, r, m;

    // find max longest non-ascending subsequence  >=
    s[0] = a[0];
    for (i = 1, j = 0; i < n; ++i)
    {
        if (noless(s[j], a[i]))
            s[++j] = a[i];
        else
            find_replace(s, j + 1, a[i], noless);

        // for (int k = 0; k <= j; ++k)
        //     printf("%d ", s[k]);
        // printf("\n");
    }

    printf("%d\n", j + 1);

    // find max longest ascending sub sequence
    // = min descending subsequences, cover all sequence
    s[0] = a[0];
    for (i = 1, j = 0; i < n; ++i)
        if (less(s[j], a[i]))
            s[++j] = a[i];
        else // binary search first just bigger, and replace
            find_replace(s, j + 1, a[i], less);
    
    printf("%d", j + 1);

    return 0;
}