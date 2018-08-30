// P1208 [USACO1.3]混合牛奶 Mixing Milk
// https://www.luogu.org/problemnew/show/P1208

#include <iostream>
#include <algorithm>

using namespace std;

struct Object
{
    int price;  // 单价
    int supply; // 供应量
} milk[5002];

bool cmp(Object &a, Object &b)
{
    return a.price < b.price;
}

int main()
{
    int n, m, i;

    cin >> n >> m;

    for (i = 0; i < m; i++)
        cin >> milk[i].price >> milk[i].supply;

    sort(milk, milk + m, cmp);

    int need = n, cost = 0, supply;

    i = 0;
    while (need > 0)
    {
        supply = min(milk[i].supply, need);

        need -= supply;
        cost += supply * milk[i++].price;
    }
    cout << cost;
}