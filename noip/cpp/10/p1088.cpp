// P1088 火星人
// https://www.luogu.org/problemnew/show/P1088


#include <cstdio>

void swap(int *a, int *b)
{
    int c = *a;
    *a = *b; *b = c;
}

bool next_permutation(int a[], int n)
{
    int i, j;
    bool flag = false;  // indicate there is a next permutation

    // reverse find first descending
    i = n - 2;
    if (i >= 0)
        while (a[i] > a[i+1]) i--;

    // find just bigger
    if (i >= 0)
    {
        j = i + 1;
        while (j < n - 1 && a[j + 1] > a[i]) j++;
        swap(&a[i], &a[j]);   // a[j] is just bigger than a[i];
        flag = true;
    }

    // reverse from [i + 1 ... n - 1]
    i = i + 1, j = n - 1;
    while (i < j)
        swap(&a[i++], &a[j--]);

    return flag;
}


int main()
{
    const int MAX_N = 10001;
    int n, m;
    int a[MAX_N];

    scanf("%d %d", &n, &m);

    for (int i = 0; i < n; ++i)
        scanf("%d", &a[i]);
    
    for (int i = 0; i < m; ++i)
        next_permutation(a, n);
    
    for (int i = 0; i < n; ++i)
        printf("%d ", a[i]);

    return 0;
}