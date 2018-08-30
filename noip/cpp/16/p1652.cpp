// P1652 圆
// https://www.luogu.org/problemnew/show/P1652

#include <iostream>

using namespace std;

#define MAX_N 100

int in_cycle(int dx, int dy, int r)
{
    return dx * dx + dy * dy < r * r;
}

int main()
{
    int n, i;
    int x[MAX_N], y[MAX_N], r[MAX_N];
    int x1, y1, x2, y2;
    cin >> n;
    for (i = 0; i < n; ++i)
        cin >> x[i];
    for (i = 0; i < n; ++i)
        cin >> y[i];
    for (i = 0; i < n; ++i)
        cin >> r[i];

    cin >> x1 >> y1 >> x2 >> y2;

    int count = 0;
    for (i = 0; i < n; ++i)
        if (in_cycle(x1 - x[i], y1 - y[i], r[i]) ^ in_cycle(x2 - x[i], y2 - y[i], r[i]))
            count++;
    cout << count;

}