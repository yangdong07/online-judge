/*
ID: yesimim1
TASK: kimbits
LANG: C++

#include <cstdio>

#include <fstream>
    ofstream fout ("kimbits.out");
    ifstream fin ("kimbits.in");
*/

#include <cstdio>

FILE *fin = fopen ("kimbits.in", "r");
FILE *fout = fopen ("kimbits.out", "w");
void _fputc(char c) { fputc(c, fout); }

const int MAX_N = 31 + 1;

int dp[MAX_N][MAX_N];

void print_bin(int n, int l)
{
    if (l == 0) return;
    print_bin(n >> 1, l - 1);
    _fputc((n & 1) ? '1' : '0');
}

void dfs_print(int n, int l, int k)
{
    // fprintf(fout, "%d %d %d %d: ", n, l, k, dp[n][l]);
    if (n == 0) return;
    if (k <= (1 << l))
    {
        print_bin(k - 1, n);
        return;
    }
    if (k <= dp[n - 1][l])  // 0
    {
        _fputc('0');
        dfs_print(n - 1, l, k);
    }
    else
    {
        _fputc('1');
        dfs_print(n - 1, l - 1, k - dp[n - 1][l]);
    }
}

int main()
{
    int n, l, k, i, j;
    fscanf(fin, "%d %d %d", &n, &l, &k);

    for (i = 0; i <= n; ++i)
    {
        dp[i][0] = 1;
        dp[i][i] = 1 << i;
    }
    for (i = 2; i <= n; ++i)
        for (j = 1; j < i; ++j)
            dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j];

    // for (i = 0; i <= n; ++i)
    // {
    //     for (j = 0; j <= n; ++j)
    //         fprintf(fout, "%-3d ", dp[i][j]);
    //     fprintf(fout, "\n");
    // }
    
    dfs_print(n, l, k);

    fprintf(fout, "\n");
    
    return 0;
}