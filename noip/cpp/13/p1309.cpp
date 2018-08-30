
#include <iostream>
#include <algorithm>

using namespace std;

#define MAX_N 200010
#define MAX_M 100010

int r[MAX_N];   // rank
int s[MAX_N];   // score
int w[MAX_N];   // weight
int win[MAX_M], los[MAX_M]; 

bool cmp(int a, int b)
{
    if (s[a] != s[b])
        return s[a] > s[b];
    return a < b;
}

// merge a, b into c
int merge(int c[], int a[], int n, int b[], int m)
{
    int i = 0, j = 0, k = 0;
    while (i < n && j < m)
        if (cmp(a[i], b[j]))
            c[k++] = a[i++];
        else
            c[k++] = b[j++];
    while (i < n)
        c[k++] = a[i++];
    while (j < m)
        c[k++] = b[j++];
    return k;
}

void compete(int n)
{
    int i, j, a, b;
    for (i = 0, j = 0; i < n; i += 2, ++j)
    {
        a = r[i];
        b = r[i + 1];
        if (w[a] > w[b])
        {
            s[a]++;
            win[j] = a;
            los[j] = b;
        }
        else
        {
            s[b]++;
            win[j] = b;
            los[j] = a;
        }
    }
}


int main()
{
    int n, i, t, q;
    cin >> n >> t >> q;

    for (i = 0; i < n * 2; ++i)
    {
        cin >> s[i];
        r[i] = i;
    }
    for (i = 0; i < n * 2; ++i)
        cin >> w[i];

    sort(r, r + n * 2, cmp);

    while (t--)
    {
        compete(n * 2);
        merge(r, win, n, los, n);
        // for (int j = 1; j <= 10; ++j)
        //     printf("%d:%d ", r[j], s[r[j]]);
        // printf("\n");
    }

    cout << r[q - 1] + 1;
    return 0;
}