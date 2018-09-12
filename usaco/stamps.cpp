/*
ID: yesimim1
TASK: stamps
LANG: C++

#include <cstdio>
FILE *fin = fopen ("stamps.in", "r");
FILE *fout = fopen ("stamps.out", "w");

void _fputc(char c) { fputc(c, fout); }

#include <fstream>
    ofstream fout ("stamps.out");
    ifstream fin ("stamps.in");
*/

#include <cstdio>
#include <algorithm>

using namespace std;

const int MAX_N = 50;
const int MAX_M = 200;
const int MAX_W = MAX_M * 10000 + 1;
const int INF = 0x3f3f3f3f;


int dp[MAX_W];
// dp(n, w)表示最少可以用多少张 n 种邮票组成面值 w。
// dp(n, w) = min(dp(n - 1, w), dp(n, w - wn) + 1)

int main()
{
    FILE *fin = fopen("stamps.in", "r");
    FILE *fout = fopen("stamps.out", "w");

    int n, m, i;
    fscanf(fin, "%d %d", &m, &n);

    int weight[MAX_N], max_w = 0;
    for (i = 0; i < n; ++i)
    {
        fscanf(fin, "%d", &weight[i]);
        max_w = max(max_w, weight[i]);
    }
    // fprintf(fout, "%d", max_w);

    int w, W = m * max_w;
    dp[0] = 0;
    for (w = 1; w <= W; ++w)
        dp[w] = INF;

    for (i = 0; i < n; i++)
    {
        for (w = weight[i]; w <= W; ++w)
            dp[w] = min(dp[w], dp[w - weight[i]] + 1);
        // for (w = 0; w <= W; ++w)
        //     fprintf(fout, "%-3d", dp[w]);
        // fprintf(fout, "\n");
    }

    for (w = 1; w <= W; ++w)
        if (dp[w] > m)
            break;
    fprintf(fout, "%d\n", w - 1);
    return 0;
}