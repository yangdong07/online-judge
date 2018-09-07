
// P1109 学生分组
// https://www.luogu.org/problemnew/show/P1109

#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
    const int MAX_N = 50;

    int s[MAX_N];

    int n, i, total = 0;
    cin >> n;
    for (i = 0; i < n; ++i)
    {
        cin >> s[i];
        total += s[i];
    }

    int l, r, a = 0, b = 0;
    cin >> l >> r;
    for (i = 0; i < n; ++i)
    {
        if (s[i] < l)
            a += l - s[i];
        if (s[i] > r)
            b += s[i] - r;
    }
    if (total > n * r || total < n * l)
        cout << "-1";
    else
        cout << max(a, b);
    return 0;
}