/*
ID: yesimim1
TASK: money
LANG: C++

#include <cstdio>

#include <fstream>
    ofstream fout ("money.out");
    ifstream fin ("money.in");
*/

#include <cstdio>

#define MAX_N 26
#define MAX_NUM 10001


int main()
{
    FILE *fin = fopen("money.in", "r");
    FILE *fout = fopen("money.out", "w");
    int n, num, i, j;
    fscanf(fin, "%d %d", &n, &num);

    int a[MAX_N];   // base
    for (i = 0; i < n; ++i)
        fscanf(fin, "%d", &a[i]);

    long long dp[MAX_NUM] = {0};
    dp[0] = 1;
    for (i = 0; i < n; ++i)
        for (j = a[i]; j <= num; ++j)
            dp[j] = dp[j] + dp[j - a[i]];

    fprintf(fout, "%lld\n", dp[num]);

    return 0;
}