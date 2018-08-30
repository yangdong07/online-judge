// P1097 统计数字
// https://www.luogu.org/problemnew/show/P1097

#include <cstdio>

#define MAX_N 200000
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

int read_num()
{
    char c;
    int num = 0;
    for (c = getchar(); c < '0' || c > '9'; c = getchar());

    for (; c >= '0' && c <= '9'; c = getchar())
        num = num * 10 + c - '0';
    return num;
}

int a[MAX_N];
int main()
{
    int n = read_num();

    int i;
    for (i = 0; i < n; ++i)
        a[i] = read_num();
    
    qsort(a, 0, n - 1);

    int x = a[0], count = 1;
    for (i = 1; i < n; ++i)
    {
        if (a[i] != x)
        {
            printf("%d %d\n", x, count);
            count = 0;
            x = a[i];
        }
        count++;
    }
    printf("%d %d\n", x, count);

    return 0;
}




/* solution 1, use map */

// #include <cstdio>
// #include <map>
// #include <algorithm>

// #define MAX_N 10001;

// int nums[MAX_N], count[MAX_N], k[MAX_N];
// bool cmp(int i, int j) { return nums[i] < nums[j]; }

// int main()
// {
//     int n, i, num;
//     n = read_num();
//     std::map<int, int> counter;

//     for (i = 0; i < n; ++i)
//     {
//         num = read_num();
//         if (counter.count(num) == 0)
//             counter[num] = 1;
//         else
//             ++counter[num];
//     }

//     std::map<int, int>::iterator it;
//     for (i = 0, it = counter.begin(); it != counter.end(); ++it, ++i)
//     {
//         nums[i] = it->first;
//         count[i] = it->second;
//         k[i] = i;
//     }

//     n = i;
//     std::sort(k, k + n, cmp);

//     for (i = 0; i < n; ++i)
//         printf("%d %d\n", nums[k[i]], count[k[i]]);

//     return 0;
// }