// P1007 独木桥
// https://www.luogu.org/problemnew/show/P1007

#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
    int l, n, p, i;
    cin >> l >> n;

    int min_time = 0, max_time = 0;

    for (i = 0; i < n; ++i)
    {
        cin >> p;
        min_time = max(min_time, min(p, l + 1 - p));
        max_time = max(max_time, max(p, l + 1 - p));
    }
    cout << min_time << " " << max_time;
}