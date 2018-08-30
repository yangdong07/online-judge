// P1908 逆序对
// https://www.luogu.org/problemnew/show/P1908


#include <cstdio>

const int MAX_N = 40002;

int a[MAX_N];
int temp[MAX_N];

int merge(int l, int r)
{
    if (l >= r) return 0;

    int m, inv_count = 0;
    int i, j, k;
    
    m = (l + r) / 2;

    inv_count = merge(l, m);
    inv_count += merge(m + 1, r);

    for(i = l, j = m + 1, k = l; i <= m && j <= r; )
    {

        if (a[i] <= a[j])
            temp[k++] = a[i++];
        else
        {
            temp[k++] = a[j++];
            inv_count += (m - i + 1);
        }
    }

    // copy rest to temp
    while (i <= m)
        temp[k++] = a[i++];
    while (j <= r)
        temp[k++] = a[j++];
    
    // copy temp back to a
    for (i = l; i <= r; ++i)
        a[i] = temp[i];

    // printf("%d %d %d\n", l, r, inv_count);
    return inv_count;
}


int main()
{
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; ++i)
        scanf("%d", &a[i]);

    int inv_count = merge(0, n - 1);

    printf("%d", inv_count);

    return 0;
}