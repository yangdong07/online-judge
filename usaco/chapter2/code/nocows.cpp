/*
ID: yesimim1
TASK: nocows
LANG: C++

#include <cstdio>
#include <fstream>
    ofstream fout ("nocows.out");
    ifstream fin ("nocows.in");
*/

#include <cstdio>

int main()
{
    const int MOD = 9901;
    const int MAX_N = 200;
    const int MAX_H = 100;

    int dp[MAX_N][MAX_H] = {0};
    int N, H, n, h;

    FILE *fin = fopen ("nocows.in", "r");
    FILE *fout = fopen ("nocows.out", "w");

    fscanf(fin, "%d%d", &N, &H);
    for (h = 1; h <= H; ++h)
        dp[1][h] = 1;
    
    for (h = 1; h <= H; ++h)
        for (n = 3; n <= N; n += 2)
            for (int k = 1; k < n; k += 2)
            {
                dp[n][h] += dp[k][h - 1] * dp[n - k - 1][h - 1];
                dp[n][h] %= MOD;
            }
    fprintf(fout, "%d\n", (dp[N][H] - dp[N][H - 1] + MOD) % MOD);
    return 0;
}