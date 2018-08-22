// P1280 尼克的任务
// https://www.luogu.org/problemnew/show/P1280

#include <cstdio>
#include <algorithm>

using namespace std;

struct task
{
    int s;  // start
    int t;  // time
};

bool cmp(task &a, task &b)
{
    return a.s < b.s;
}

int main()
{
    int n, k;
    scanf("%d %d", &n, &k);
    const int MAX_N = 10001;
    task a[MAX_N];
    int available[MAX_N] = {0}; // available task num at each time point

    for (int i = 0; i < k; ++i)
    {
        scanf("%d %d", &a[i].s, &a[i].t);
        available[a[i].s]++;
    }
    // sort tasks by start time;
    sort(a, a + k, cmp);
    // the max rest time at each time point
    // dp[i] = dp[i + 1] if no task at time i;
    // dp[i] = max(dp[i + t]) for each task(i, t) at time i;
    int dp[MAX_N] = {0};
    int task_index = k - 1;  // search from last task;

    for (int i = n; i > 0; --i)
    {
        if (!available[i])
            dp[i] = dp[i + 1] + 1;
        else
            for (int j = 0; j < available[i]; ++j, --task_index)
                dp[i] = max(dp[i], dp[i + a[task_index].t]);
    }
    // for (int i = 1; i <= n; ++i)
    //     printf("%2d ", i);
    // printf("%d\n", dp[0]);
    // for (int i = 1; i <= n; ++i)
    //     printf("%2d ", dp[i]);

    printf("%d\n", dp[1]);

    return 0;
}