// P1094 纪念品分组
// https://www.luogu.org/problemnew/show/P1094

#include <iostream>
#include <algorithm>

using namespace std;

#define MAX_N 30001

int main()
{
    int n, w, i, j;
    cin >> w >> n;
    int a[MAX_N];

    for (i = 0; i < n; ++i)
    {
        cin >> a[i];
    }

    sort(a, a + n);

    int s = 0;
    for (i = 0, j = n - 1; i < j; )
    {
        if (a[i] + a[j] > w)
        {
            ++s;
            --j;
        }
        else
        {
            ++s;
            ++i;
            --j;
        }
    }
    if (i == j)  ++s;
    cout << s << endl;
    return 0;
}