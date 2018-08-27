// P1926 小书童——刷题大军
// https://www.luogu.org/problemnew/show/P1926

#include <cstdio>
#include <algorithm>

#define MAX_N 21
#define MAX_M 21
#define MAX_TIME 101


int main()
{
    int n, m, pass_score, total_time;
    scanf("%d%d%d%d", &n, &m, &pass_score, &total_time);

    int problem[MAX_N];
    int hwtime[MAX_M], hwscore[MAX_M];
    int i;
    for (i = 0; i < n; ++i)
        scanf("%d", &problem[i]);
    for (i = 0; i < m; ++i)
        scanf("%d", &hwtime[i]);
    for (i = 0; i < m; ++i)
        scanf("%d", &hwscore[i]);
    
    int dp[MAX_TIME] = {0};
    int t;
    for (i = 0; i < m; ++i)
        for (t = total_time; t >= hwtime[i]; --t)
            dp[t] = std::max(dp[t], dp[t - hwtime[i]] + hwscore[i]);
    

    // 可以用二分查找
    for (t = 0; t <= total_time; ++t)
        if (dp[t] >= pass_score) break;

    int rest_time = total_time - t;
    // printf("%d\n", rest_time);
    std::sort(problem, problem + n);

    int cost_time = 0;
    for (i = 0; i < n; ++i)
    {
        cost_time += problem[i];
        if (cost_time > rest_time)
            break;
    }
    printf("%d", i);

    return 0;
}