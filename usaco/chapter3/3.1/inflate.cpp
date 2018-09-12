/*
ID: yesimim1
TASK: inflate
LANG: C++

#include <cstdio>

#include <fstream>
    ofstream fout ("inflate.out");
    ifstream fin ("inflate.in");
*/

#include <cstdio>

int max(int a, int b) { return a > b ? a : b; }

int main()
{
    FILE *fin = fopen ("inflate.in", "r");
    FILE *fout = fopen ("inflate.out", "w");
    const int MAX_T = 10001;
    int T, n;
    fscanf(fin, "%d %d", &T, &n);

    int ti, si, t;
    int dp[MAX_T] = {0};
    for (int i = 0; i < n; ++i)
    {
        fscanf(fin, "%d %d", &si, &ti);
        for (t = ti; t <= T; ++t)
            dp[t] = max(dp[t], dp[t - ti] + si);
    }
    fprintf(fout, "%d\n", dp[T]);
    return 0;
}