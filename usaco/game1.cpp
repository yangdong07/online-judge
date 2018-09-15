/*
ID: yesimim1
TASK: game1
LANG: C++

#include <cstdio>
void _fputc(char c) { fputc(c, fout); }

#include <fstream>
    ofstream fout ("game1.out");
    ifstream fin ("game1.in");
*/

#include <cstdio>
#include <algorithm>

using namespace std;

int main()
{
    FILE *fin = fopen("game1.in", "r");
    FILE *fout = fopen("game1.out", "w");

    const int MAX_N = 200 + 1;
    int n, i;
    int a[MAX_N], sum[MAX_N] = {0};

    fscanf(fin, "%d", &n);
    for (i = 1; i <= n; ++i)
    {
        fscanf(fin, "%d", &a[i]);
        sum[i] = sum[i - 1] + a[i];
    }

    int dp[MAX_N + 1] = {0};  // dp(i, k) ~ [i, i + k]

    for (int k = 0; k < n; ++k)
        for (i = 1; i + k <= n; ++i)
            dp[i] = sum[i + k] - sum[i - 1] - min(dp[i], dp[i + 1]);
    
    // for (i = 0; i <= n; ++i)
    //     fprintf(fout, "%d ", dp[i]);
    // fprintf(fout, "\n");

    fprintf(fout, "%d %d\n", dp[1], sum[n] - dp[1]);


    return 0;
}