// P1056 排座椅
// https://www.luogu.org/problemnew/show/P1056


#include <iostream>
#include <utility> 
#include <cstring>
#include <algorithm>

using namespace std;

#define MAX_N  1001

typedef pair<int, int>  vip;   // value-index pair

bool vip_cmp1r(const vip& a, const vip& b)
{
    return a.first > b.first;   // larger front
}

bool vip_cmp2(const vip& a, const vip& b)
{
    return a.second < b.second;   // small front
}

int main()
{
    // m for row, n for column
    // k for horizontal, l for vertical
    // d for pairs
    // x, y : position
    int m, n, k, l, d, x1, y1, x2, y2;
    cin >> m >> n >> k >> l >> d;

    // counter
    int h[MAX_N] = { 0 }, v[MAX_N] = { 0 }; // h for horizontal, v for vertical
    for (int i = 0; i < d; ++i)
    {
        cin >> x1 >> y1 >> x2 >> y2;
        if (x1 == x2) // vertical
            v[min(y1, y2)]++;
        else if (y1 == y2)
            h[min(x1, x2)]++;
    }

    // sort
    int i;
    vip hi[MAX_N], vi[MAX_N]; 
    for (i = 1; i <= m; ++i)
        hi[i] = make_pair(h[i], i);
    for (i = 1; i <= n; ++i)
        vi[i] = make_pair(v[i], i);

    sort(hi + 1, hi + m + 1, vip_cmp1r);
    sort(hi + 1, hi + k + 1, vip_cmp2);
    sort(vi + 1, vi + n + 1, vip_cmp1r);
    sort(vi + 1, vi + l + 1, vip_cmp2);

    // output
    for (i = 1; i <= k; ++i)
        cout << hi[i].second << " ";
    cout << endl;
    for (i = 1; i <= l; ++i)
        cout << vi[i].second << " ";
    cout << endl;

}