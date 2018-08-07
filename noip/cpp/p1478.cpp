// P1478 陶陶摘苹果（升级版）
// https://www.luogu.org/problemnew/show/P1478

#include <iostream>
#include <algorithm>

using namespace std;

#define MAX_N 5001
#define MAX_INT 1000000000

int main()
{
    int n, s;  // apples
    int a, b;  // a for chair, b for taotao
    int x, y, cost[MAX_N];

    cin >> n >> s >> a >> b;

    for (int i = 0; i < n; ++i)
    {
        cin >> x >> y;
        cost[i] = (x <= a + b) ? y : MAX_INT;
    }

    sort(cost, cost + n);

    int count = 0;
    for (int i = 0; i < n && s >= cost[i]; ++i)
    {
        s -= cost[i];
        count++;
    }
    cout << count;
}