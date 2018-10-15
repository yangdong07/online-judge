
// P1016 旅行家的预算
// https://www.luogu.org/problemnew/show/P1016

#include <cstdio>
#include <iostream>

using namespace std;

int main()
{
    const int MAX_N = 6 + 2;
    int n, i;
    double distance, capacity, dpl, step;
    double price[MAX_N], dist[MAX_N]; 
    cin >> distance >> capacity >> dpl >> price[0] >> n;

    step = dpl * capacity;

    dist[0] = 0;
    for (i = 1; i <= n; ++i)
        cin >> dist[i] >> price[i];
    dist[n + 1] = distance;
    price[n + 1] = 0;
    
    double d, percent[MAX_N], cost;
    percent[0] = 1.0;
    cost = price[0];
    for (int cur = 1; cur <= n + 1; ++cur)
    {
        d = dist[cur] - dist[cur - 1];
        if (d > step)
        {
            cout << "No Solution" << endl;
            return 0;
        }
        // 先消耗
        percent[cur] = 0.0;
        // cout << endl << "at " << cur << endl;
        // for (i = 0; i <= n + 1; ++i)
        //     cout << percent[i] << " ";
        // cout << endl;

        for (i = 0; i < cur; ++i)
        {
            if (d < percent[i] * step)
            {
                percent[i] -= d / step;
                percent[cur] += d / step;
                break;
            }
            else
            {
                d -= percent[i] * step;
                percent[cur] += percent[i];
                percent[i] = 0.0;
            }
        }
        // cout << cost << endl;
        // for (i = 0; i <= n + 1; ++i)
        //     cout << percent[i] << " ";
        // cout << endl;

        cost += price[cur] * percent[cur];

        // 再补充。 如果当前价格比之前的低，就换掉。
        for (i = cur - 1; i >= 0; --i)
        {
            if (price[cur] < price[i])
            {
                cost -= (price[i] - price[cur]) * percent[i];
                percent[cur] += percent[i];
                percent[i] = 0.0;
            }
        }
        // cout << cost << endl;
    }

    // // 把所有油都退掉
    // for (i = 0; i <= n; ++i)
    // {
    //     if (percent[i] > 0.0)
    //         cost -= price[i] * percent[i] * capacity;
    // }
    printf("%.2lf", cost * capacity);

    return 0;
}