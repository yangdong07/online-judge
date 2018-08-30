// P2036 Perket
// https://www.luogu.org/problemnew/show/P2036

#include <iostream>
#include <cstdlib>
#include <algorithm>

using namespace std;

#define MAX_N 11

int a[MAX_N] = {0}, b[MAX_N] = {0};
int mask[MAX_N] = {0};

int main()
{
    int n, i;
    cin >> n;

    for (i = 0; i < n; ++i)
    {
        cin >> a[i] >> b[i];
        mask[i] = 1 << i;
    }
    int aa, bb;
    int min_diff = abs(a[0] - b[0]);
    for (int c = 1; c < (1 << n); ++c)
    {
        aa = 1;
        bb = 0;
        for (i = 0; i < n; ++i)
        {
            if (c & mask[i])
            {
                aa *= a[i];
                bb += b[i];
            }
        }
        min_diff = min(min_diff, abs(aa - bb));
    }

    cout << min_diff;
}