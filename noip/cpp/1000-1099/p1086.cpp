// P1086 花生采摘
// https://www.luogu.org/problemnew/show/P1086

#include <iostream>
#include <cstdlib>
#include <utility>
#include <algorithm>

using namespace std;

typedef pair<int, int> vip;

const int MAX_N = 20 * 20 + 2;

bool vip_cmp1r(const vip& a, const vip& b)
{
    return a.first > b.first;
}

int main()
{
    int m, n, k;
    int a[MAX_N] = { 0 };
    cin >> m >> n >> k;

    int i;
    for (i = 0; i < m * n; ++i)
        cin >> a[i];

    vip vi[MAX_N];
    for (i = 0; i < m * n; ++i)
        vi[i] = make_pair(a[i], i);
    
    sort(vi, vi + m * n, vip_cmp1r);

    int px = 0, py = 0;  // current pos
    int x, y;    // target pos
    int t, rest = k;  // estimate time, rest time
    int count = 0; // counter
    for (int j = 0; j < m * n; ++j)
    {
        i = vi[j].second;
        x = i / n + 1;
        y = i % n + 1;
        t = j == 0 ? x : abs(x - px) + abs(y - py);
        t++;   // pick cost 1 time unit
        // printf("%d %d %d %d %d %d %d\n", px, py, x, y, vi[j].first, t, rest);

         // consider back to road
        if (t + x > rest) break;

        rest -= t;
        count += vi[j].first;
        px = x;
        py = y;
    }
    cout << count << endl;
}