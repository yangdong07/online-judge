// P1025 数的划分
// https://www.luogu.org/problemnew/show/P1025

#include <iostream>

using namespace std;

const int MAX_N = 201;
int dp[MAX_N][MAX_N] = { 0 };

int partition(int n, int k)
{
    if (n < k) return 0;
    if (n == k || k == 1) return 1;

    if (dp[n][k]) return dp[n][k];

    dp[n][k] = partition(n - 1, k - 1) + partition(n - k, k);
    return dp[n][k];
}

int main()
{
    int n, k;
    cin >> n >> k;
    cout << partition(n, k);
    return 0;
}