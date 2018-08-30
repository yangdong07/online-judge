// P1679 神奇的四次方数
// https://www.luogu.org/problemnew/show/P1679

#include <cstdio>
#include <algorithm>

#define MAX_N 20
#define MAX_M 100001

using namespace std;

int main()
{
    int m, i, j;
    scanf("%d", &m);

    int pow4[MAX_N];
    for (i = 1; i < MAX_N; ++i)
        pow4[i] = i * i * i * i;

    int p;
    int dp[MAX_M];
    for (j = 0; j <= m; ++j)
        dp[j] = j;    //  j = (1^4) * j

    for (i = 2; i < MAX_N; ++i)
    {
        p = pow4[i];
        for (j = p; j <= m; ++j)
            dp[j] = min(dp[j], dp[j - p] + 1);
    }
    printf("%d", dp[m]);
    
    return 0;
}