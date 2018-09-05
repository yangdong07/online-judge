/*
ID: yesimim1
TASK: subset
LANG: C++

#include <cstdio>

#include <fstream>
    ofstream fout ("subset.out");
    ifstream fin ("subset.in");
*/

#include <cstdio>

int main()
{
    FILE *fin = fopen ("subset.in", "r");
    FILE *fout = fopen ("subset.out", "w");
    const int MAX_SUM = 40 * 39 / 2;
    int n;
    fscanf(fin, "%d", &n);
    int sum = (n + 1) * n / 2;
    if (sum & 1)
    {
        fprintf(fout, "0\n");
        return 0;
    }
    sum /= 2;
    long long dp[MAX_SUM] = {0};

    dp[0] = 1;
    for (int i = 1; i <= n; ++i)
    {
        for (int s = sum; s >= i; --s)
            dp[s] += dp[s - i];
        
        // fprintf(fout, "dp(%d, w): ", i);
        // for (int s = 1; s <= sum; ++s)
        //     fprintf(fout, "%d ", dp[s]);
        // fprintf(fout, "\n");
    }
    
    fprintf(fout, "%lld\n", dp[sum] / 2);

    return 0;
}