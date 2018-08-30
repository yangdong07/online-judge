// P2141 珠心算测验
// https://www.luogu.org/problemnew/show/P2141

#include <iostream>
#include <algorithm>

using namespace std;

int a[101];

int main()
{
    int n, i;
    cin >> n;
    for (i = 0; i < n; i++)
        cin >> a[i];

    sort(a, a + n);

    int count = 0;
    int l, r;
    for (i = n - 1; i >= 2; --i)
    {
        l = 0, r = i - 1;
        while (l < r)
        {
            if (a[l] + a[r] < a[i])
                ++l;
            else if (a[l] + a[r] > a[i])
                --r;
            else
            {
                count++;
                break;
            }
        }
    }
    cout << count;
}