/*
ID: yesimim1
TASK: numtri
LANG: C++

#include <cstdio>

#include <fstream>
    ofstream fout ("numtri.out");
    ifstream fin ("numtri.in");
*/

#include <cstdio>
#include <algorithm>

using namespace std;

int main()
{
    FILE *fin = fopen ("numtri.in", "r");
    FILE *fout = fopen ("numtri.out", "w");
    const int MAX_N = 1001;
    int a[MAX_N], dp[MAX_N];
    int n, i, j;

    fscanf(fin, "%d", &n);

    fscanf(fin, "%d", &a[1]);  // first line
    dp[1] = a[1];
    for (i = 2; i <= n; ++i)
    {
        for (j = 1; j <= i; ++j)
            fscanf(fin, "%d", &a[j]);
        
        dp[i] = dp[i - 1] + a[i];
        for (j = i - 1; j > 1; --j)
            dp[j] = max(dp[j], dp[j - 1]) + a[j];
        dp[1] = dp[1] + a[1];

        // for (j = 1; j <= i; ++j)
        //     fprintf(fout, "%d:%d ", a[j], dp[j]);
        // fprintf(fout, "\n");
    }

    int max_sum = 0;
    for (i = 1; i <= n; ++i)
        max_sum = max(max_sum, dp[i]);

    fprintf(fout, "%d\n", max_sum);

}
