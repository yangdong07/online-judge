// P1003 铺地毯
// https://www.luogu.org/problemnew/show/P1003

#include <iostream>

using namespace std;

#define MAX_N 10010

int a[MAX_N], b[MAX_N], g[MAX_N], k[MAX_N];

int main()
{
    int n, i, x, y;
    cin >> n;
    for (i = 1; i <= n; i++)
    {
        cin >> a[i] >> b[i] >> g[i] >> k[i];
    }
    cin >> x >> y;
    for (i = n; i > 0; i--)
    {
        if (x >= a[i] && x <= a[i] + g[i] && y >= b[i] && y <= b[i] + k[i])
        {
            cout << i;
            return 0;
        }
    }
    cout << -1; 
}