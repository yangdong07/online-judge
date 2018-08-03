// P2689 东南西北
// https://www.luogu.org/problemnew/show/P2689


#include <iostream>
#include <cstdlib>

using namespace std;

int main()
{
    int x1, y1, x2, y2, t;
    cin >> x1 >> y1 >> x2 >> y2 >> t;

    int dx = x2 - x1, dy = y2 - y1;
    char c;
    int i, step = 0;
    for (i = 0; i < t; i++)
    {
        if (dx == 0 && dy == 0) break;

        cin >> c;
        if (c == 'N' && dx > 0)
            ++step, --dx;
        else if (c == 'E' && dy > 0)
            ++step, --dy;
        else if (c == 'S' && dx < 0)
            ++step, ++dx;
        else if (c == 'W' && dy < 0)
            ++step, ++dy;
    }
    if (dx || dy) cout << -1;
    else cout << step;
}