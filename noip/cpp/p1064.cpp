// P1064 金明的预算方案
// https://www.luogu.org/problemnew/show/P1064

#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

struct object
{
    int v;
    int vw;
    int num;
    object(int v, int vw, int n) : v(v), vw(vw), num(n) {}
};

void attach(vector<object> &combo, int v, int vw)
{
    int n = combo.size();
    for (int i = 0; i < n; ++i)
        if (combo[i].num < 2)
            combo.push_back(object(combo[i].v + v,
                                   combo[i].vw + vw, 
                                   combo[i].num + 1));
}

void update_dp(int dp[], vector<object> &combo, int n)
{
    vector<object>::iterator it;
    int i, best;

    // for (it = combo.begin(); it != combo.end(); ++it)
    //     printf("%d %d %d\n", it->v, it->vw, it->num);
    // printf("\n");

    for (i = n; i > 0; --i)
    {
        best = dp[i];
        for (it = combo.begin(); it != combo.end(); ++it)
            if (i >= it->v)
                best = max(best, dp[i - it->v] + it->vw);
        dp[i] = best;
    }
}

int main()
{
    const int MAX_M = 70;    // 最大物品数量
    const int MAX_N = 32001; // 最大钱数

    vector<object> objs[MAX_M];

    int n, m;   // n 钱数上限； m 物品数量
    scanf("%d %d", &n, &m);

    n /= 10;

    int v, w, id;
    for (int i = 1; i <= m; ++i)
    {
        scanf("%d %d %d", &v, &w, &id);
        if (!id)
            objs[i].push_back(object(v / 10, v / 10 * w, 0));
        else
            attach(objs[id], v / 10, v / 10 * w);
    }

    int dp[MAX_N] = { 0 };
    for (int i = 1; i <= m; ++i)
        if (objs[i].size() > 0)
            update_dp(dp, objs[i], n);
    
    printf("%d", dp[n] * 10);

    return 0;
}