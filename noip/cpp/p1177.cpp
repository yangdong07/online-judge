// P1177 【模板】快速排序
// https://www.luogu.org/problemnew/show/P1177

#include <cstdio>
#include <algorithm>

#define CUTOFF  (10)

void swap(int *a, int *b)
{
    int c = *a; *a = *b; *b = c;
}

// insertion sort
void isort(int a[], int n)
{
    int i, j, tmp;
    for (i = 1; i < n; ++i)
    {
        tmp = a[i];
        for (j = i; j > 0 && a[j - 1] > tmp; --j)
            a[j] = a[j - 1];
        a[j] = tmp;
    }
}

// median3
int median3(int a[], int left, int right)
{
    int mid = (left + right) / 2;
    if (a[left] > a[mid])
        swap(&a[left], &a[mid]);
    if (a[left] > a[right])
        swap(&a[left], &a[right]);
    if (a[mid] > a[right])
        swap(&a[mid], &a[right]);
    
    swap(&a[mid], &a[right - 1]);   // hide pivot;
    return a[right - 1];
}

// quick sort
void qsort(int a[], int left, int right)
{
    if (right <= left + CUTOFF)
       return isort(a + left, right - left + 1);

    /* partition */
    int pivot = median3(a, left, right);
    int i = left, j = right - 1;

    for (;;)
    {
        while (a[++i] < pivot) ;
        while (a[--j] > pivot) ;
        if (i < j)
            swap(&a[i], &a[j]);
        else
            break;
    }
    swap(&a[i], &a[right - 1]);

    /* recursion */
    qsort(a, left, i - 1);
    qsort(a, i + 1, right);
}

int main()
{
    const int MAX_N = 100001;
    int n, i;
    int a[MAX_N];
    scanf("%d", &n);
    for (i = 0; i < n; ++i)
        scanf("%d", &a[i]);
    qsort(a, 0, n - 1);
    // std::sort(a, a + n);

    for (i = 0; i < n; ++i)
        printf("%d ", a[i]);
}