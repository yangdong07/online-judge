// P1023 税收与补贴问题
// https://www.luogu.org/problemnew/show/P1023

#include <iostream>
#include <cstdlib>
#include <algorithm>

using namespace std;

#define MAX_N 100002


int sales[MAX_N] = { 0 };

// calculate sales @price, 开了一个大数组，比较浪费空间
int g(int price, int mp, int reduce)
{
    if (price > mp)
        return sales[mp] - (price - mp) * reduce;
    if (sales[price])
        return sales[price];
    
    // interpolation
    int i = price, j = price;
    while (i > 0 && !sales[i]) --i;
    while (j < mp && !sales[j]) ++j;

    sales[price] = sales[i] + ((sales[j] - sales[i]) / (j - i)) * (price - i);
    return sales[price];
}

int main()
{
    int ep, cost; // 预期价格 ，成本
    int price, sale;  // 售价，销量
    cin >> ep >> cost;
    cin >> sales[cost];

    int mp = cost;  // 已知最大价格
    while (1)
    {
        cin >> price >> sale;
        if (price == -1 && sale == -1) break;
        sales[price] = sale;
        mp = max(price, mp);
    }
    int reduce; // 增加 1块钱，减少的销售量。
    cin >> reduce;

    int s1, s2, s3;
    s1 = g(ep - 1, mp, reduce);    // profit = ep - 1 - cost
    s2 = g(ep, mp, reduce);        // profit = ep - cost
    s3 = g(ep + 1, mp, reduce);    // profit = ep + 1 - cost

    int r1, r2, r3;  // revenue

    int bonus, min_bonus = 1000000000;
    int max_revenue = 0;
    // profit = price - cost + bonus

    for (int profit = 0; ; ++profit)
    {
        r1 = s1 * (profit - 1);
        r2 = s2 * profit;
        r3 = s3 * (profit + 1);
        // cout << profit + cost - ep << endl;
        // cout << s1 << " " << r1 << endl;
        // cout << s2 << " " << r2 << endl;
        // cout << s3 << " " << r3 << endl;
        if (r1 > r2 && r2 > r3) break;

        bonus = profit + cost - ep;

        if (r1 <= r2 && r2 >= r3)
        {
            if (r2 >= max_revenue && abs(bonus) < abs(min_bonus))
            {
                min_bonus = bonus;
                max_revenue = r2;
            }
        }
    }
    if (max_revenue)
        cout << min_bonus << endl;
    else
        cout << "NO SOLUTION" << endl;
    return 0;
}