// P1433 吃奶酪
// https://www.luogu.org/problemnew/show/P1433


/* solution1,  naive permutation */

/*
#include <cstdio>
#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

const int MAX_N = 20;

int n;
bool v[MAX_N] = {false};
double x[MAX_N], y[MAX_N];
double d[MAX_N][MAX_N]; // 任意两点之间的距离
double min_trip = 1e304;   // 先给一个比较大的数

void dfs(int cur, int step, double trip)
{
    if (trip > min_trip) return;
    if (step >= n)
    {
        min_trip = min(min_trip, trip);
        return;
    }
    for (int i = 1; i <= n; i++)
        if (!v[i])
        {
            v[i] = true;
            dfs(i, step + 1, trip + d[cur][i]);
            v[i] = false;
        }
}

int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> x[i] >> y[i];

    x[0] = 0.0;
    y[0] = 0.0;
    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= n; j++)
            d[i][j] = sqrt((x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]));

    dfs(0, 0, 0.0);

    printf("%.2f", min_trip);
    return 0;
}
*/

#include <cstdio>
#include <cmath>
#include <algorithm>

using namespace std;

const int MAX_N = 16;
const int MAX_S = (1 << 16) - 1;  // 动态规划需要指数级的空间
const double MAX_DP = 1e304;      // 大大大

int n;
double x[MAX_N], y[MAX_N];
double d[MAX_N][MAX_N];  // 任意两点之间的距离
double dp[MAX_N][MAX_S]; // 动态规划解， dp[i][s] 表示从 i点访问 S 集合的最小遍历距离

void dp_solve()
{
    int s, i, j;
    for (s = 1; s < (1 << n); ++s)
        for (i = 1; i <= n; ++i)
        {
            if (s & (1 << (i - 1)))
            {
                dp[i][s] = dp[i][s - (1 << (i - 1))];
                // printf("%d %d %lf\n", i, s, dp[i][s]);
                continue;
            }
            dp[i][s] = MAX_DP;
            for (j = 1; (1 << (j - 1)) <= s; ++j) 
            {
                if (s & (1 << (j - 1)))
                    dp[i][s] = min(dp[i][s], dp[j][s - (1 << (j - 1))] + d[i][j]); 
            }
            // printf("%d %d %lf\n", i, s, dp[i][s]);
        }
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%lf %lf", &x[i], &y[i]);

    x[0] = 0.0;
    y[0] = 0.0;
    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= n; j++)
            d[i][j] = sqrt((x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]));

    dp_solve();

    double min_trip = MAX_DP;
    for (int i = 1; i <= n; ++i)
        min_trip = min(min_trip, dp[i][(1 << n) - 1] + d[0][i]);

    printf("%.2f", min_trip);
    return 0;
}