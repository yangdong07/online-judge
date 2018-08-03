// P2637 第一次，第二次，成交！
// https://www.luogu.org/problemnew/show/P2637

#include <cstdio>
#include <algorithm>

using namespace std;

#define MAX_M 1001

int main()
{
    int n, m, i;
    int price[MAX_M] = { 0 };
    scanf("%d %d", &n, &m);
    for (i = 0; i < m; ++i)
        scanf("%d", &price[i]);

    sort(price, price + m);

    int minPrice = 0, maxRevenue = 0;
    // n > m 供大于求
    // n < m 供不应求
    for (i = max(0, m - n); i < m; ++i)
    {
        if (price[i] * (m - i) > maxRevenue)
        {
            maxRevenue = price[i] * (m - i);
            minPrice = price[i];
        }
    }
    printf("%d %d", minPrice, maxRevenue);
}