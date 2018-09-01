
// P1460 健康的荷斯坦奶牛 Healthy Holsteins
// https://www.luogu.org/problemnew/show/P1460

#include <cstdio>


const int MAX_N = 25;
const int MAX_M = 15;


int n, m;
int vitamins[MAX_N];   // vitamins
int feeds[MAX_M + 1][MAX_N];   // feeds

bool enough(int s[])
{
    for (int i = 0; i < n; ++i)
        if (s[i] < vitamins[i]) return false;
    return true;
}

int supply[MAX_N] = {0};
int solution[MAX_M + 1];
bool find_solution = false;

void dfs(int select, int d, int max_depth)
{
    if (d == max_depth)
    {
        if (enough(supply))
        {
            printf("%d", d);
            for (int i = 1; i <= d; ++i)
                printf(" %d", solution[i]);
            printf("\n");
            find_solution = true;
        }
        return;
    }

    int i, k;
    for (k  = select + 1; k <= m; ++k)
    {
        for (i = 0; i < n; ++i)
            supply[i] += feeds[k][i];
        solution[d + 1] = k;
        dfs(k, d + 1, max_depth);
        if (find_solution) return;
        for (i = 0; i < n; ++i)
            supply[i] -= feeds[k][i];
    }
}

int main()
{
    int i, j;
    scanf("%d", &n);
    for (i = 0; i < n; ++i)
        scanf("%d", &vitamins[i]);
    
    scanf("%d", &m);
    for (i = 1; i <= m; ++i)
        for (j = 0; j < n; ++j)
            scanf("%d", &feeds[i][j]);
    
    for (int depth = 1; depth <= m && !find_solution; ++depth)
        dfs(0, 0, depth);
    
    return 0;
}