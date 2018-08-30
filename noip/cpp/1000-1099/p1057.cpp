// P1057 传球游戏
// https://www.luogu.org/problemnew/show/P1057

#include <iostream>

using namespace std;

const int MAX_N = 33;

int dp[MAX_N][MAX_N] = {0};

int main()
{
    int n, m;
    cin >> n >> m;

    int i, j;
    dp[0][0] = 1;

    for (j = 1; j <= m; ++j)
        for (i = 0; i < n; ++i)
            dp[i][j] = dp[(i + 1) % n][j - 1] + dp[(n + i - 1) % n][j - 1];
    
    cout << dp[0][m];

    return 0;
}