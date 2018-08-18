// P1192 台阶问题
// https://www.luogu.org/problemnew/show/P1192

#include <iostream>

using namespace std;

int main()
{
    const int MAX_K = 102;
    const int MOD = 100003;
    int n, k;
    cin >> n >> k;

    int i, j, t, kplus = k + 1;
    int dp[MAX_K];

    dp[0] = dp[1] = 1;
    for (i = 2; i < kplus; ++i)
        dp[i] = (dp[i - 1] << 1) % MOD;

    for (i = kplus; i <= n; ++i)
    {
        t = 0;
        for (j = 1; j < kplus; ++j)
            t = (t + dp[(i + j) % kplus]) % MOD;
        dp[i % kplus] = t;
    }
    // for (i = 0; i < kplus; ++i)
    //     cout << dp[i] << " ";
    cout << dp[n % kplus];
    return 0;
}