// P1116 车厢重组
// https://www.luogu.org/problemnew/show/P1116

#include <cstdio>

using namespace std;

#define  MAX_N 10000

int  _mergeSort(int a[], int b[], int l, int r);
int merge(int a[], int b[], int l, int m, int r);
 
int mergeSort(int arr[], int array_size)
{
    int b[array_size];
    return _mergeSort(arr, b, 0, array_size - 1);
}

int _mergeSort(int a[], int b[], int l, int r)
{
    int count = 0;
    if (l < r)
    {
        int m = (l + r) / 2;
        count = _mergeSort(a, b, l, m);
        count += _mergeSort(a, b, m + 1, r);
        count += merge(a, b, l, m + 1, r);
    }
    return count;
}
 
int merge(int a[], int b[], int l, int m, int r)
{
    int i = l, j = m, k = l;
    int count = 0;

    while ((i <= m - 1) && (j <= r))
    {
        if (a[i] <= a[j])
            b[k++] = b[i++];
        else
        {
            b[k++] = a[j++];
            count += (m - i);
        }
    }
    while (i <= m - 1) b[k++] = a[i++];
    while (j <= r) b[k++] = a[j++];

    for (i = l; i <= r; i++) a[i] = b[i];

    return count;
}

int main() {
    int n, num[MAX_N];
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &num[i]);
    }

    // // O(N^2)
    // int count = 0;
    // for (int i = 0; i < n; ++i )
    //     for (int j = i + 1; j < n; ++j)
    //         if (num[i] > num[j]) count++;
    // printf("%d", count);

    // merge sort
    printf("%d", mergeSort(num, n));
}