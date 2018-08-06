// P1002 过河卒
// https://www.luogu.org/problemnew/show/P1002

#include <iostream>

using namespace std;

#define MAX_SIZE  21

typedef long long ll;

ll dp[MAX_SIZE][MAX_SIZE] = { 0 };
const int dx[9] = {0, 1, 1, 2, 2, -1, -1, -2, -2};
const int dy[9] = {0, 2, -2, 1, -1, 2, -2, 1, -1};

int main()
{
    int n, m, x, y;
    int i, j;
    cin >> n >> m >> x >> y;

    // fill hourse...

    int xx, yy;
    for (i = 0; i < 9; ++i)
    {
        xx = x + dx[i];
        yy = y + dy[i];
        if (xx >= 0 && xx <= n && yy >= 0 && yy <= m) dp[xx][yy] = -1;
    }

    // dp 
    dp[0][0] = dp[0][0] == -1 ? 0 : 1;
    for (j = 1; j <= m; ++j)
        dp[0][j] = dp[0][j] == -1 ? 0 : dp[0][j - 1];
    for (i = 1; i <= n; ++i)
        dp[i][0] = dp[i][0] == -1 ? 0 : dp[i - 1][0];

    for (i = 1; i <= n; ++i)
        for (j = 1; j <= m; ++j)
            dp[i][j] = dp[i][j] == -1 ? 0 : dp[i - 1][j] + dp[i][j - 1];

    cout << dp[n][m];

}