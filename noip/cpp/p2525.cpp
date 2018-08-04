// P2525 Uim的情人节礼物·其之壱
// https://www.luogu.org/problemnew/show/P2525

#include <cstdio>
#include <algorithm>

#define MAX_N 11

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

bool prev_permutation(int a[], int n)
{
    int i, j;
    // indicate there is a prev permutation
    bool flag = false;  

    // reverse find first ascending
    i = n - 2;
    if (i >= 0)
        while (a[i] < a[i+1]) i--;

    if (i >= 0)
    {
        j = i + 1;
        while (j < n - 1 && a[j + 1] < a[i]) j++;
        swap(&a[i], &a[j]);  // a[j] is just small than a[i]
        flag = true;
    }

    // reverse from [i + 1 ... n - 1]
    i = i + 1, j = n - 1;
    while (i < j)
        swap(&a[i++], &a[j--]);

    return flag;
}


void test_permutations()
{
    const int n = 7;
    int a[n], b[n], i;
    for (i = 0; i < n; ++i)
    {
        a[i] = n - i;
        b[i] = n - i;
    }
    
    while (prev_permutation(a, n))
    {
        std::prev_permutation(b, b + n);
        for (i = 0; i < n; ++i)
            printf("%d ", a[i]);
        printf("\n");
        for (i = 0; i < n; ++i)
            printf("%d ", b[i]);
        printf("\n");
        for (i = 0; i < n; ++i)
            if (a[i] != b[i])
            {
                printf("error, %d %d %d\n", i, a[i], b[i]);
                return;
            }
        printf("\n");
    }
    printf("OK\n");
}

int main()
{
    int n, i;
    int a[MAX_N] = { 0 };

    scanf("%d", &n);

    for (i = 0; i < n; ++i)
        scanf("%d", &a[i]);

    if (prev_permutation(a, n))
        for (i = 0; i < n; ++i)
            printf("%d ", a[i]);
    else
        printf("ERROR");
}