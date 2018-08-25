// P1541 乌龟棋
// https://www.luogu.org/problemnew/show/P1541

#include <cstdio>


int max(int a, int b) { return a > b ? a : b; }

const int MAX_N = 351;
const int MAX_M = 41;

int n, m;
int grid[MAX_N];
int cards[5] = {0, 0, 0, 0, 0}; // cards

int dp[MAX_M][MAX_M][MAX_M][MAX_M] = {0}; //!!!

int dfs_play(int a, int b, int c, int d, int step)
{
    if (step == n)
        return grid[step];
    if (dp[a][b][c][d]) return dp[a][b][c][d];

    int max_s = 0;

    if (a > 0)
        max_s = max(max_s, dfs_play(a - 1, b, c, d, step + 1));
    if (b > 0)
        max_s = max(max_s, dfs_play(a, b - 1, c, d, step + 2));
    if (c > 0)
        max_s = max(max_s, dfs_play(a, b, c - 1, d, step + 3));
    if (d > 0)
        max_s = max(max_s, dfs_play(a, b, c, d - 1, step + 4));
    
    return dp[a][b][c][d] = max_s + grid[step];
}

int main()
{
    scanf("%d %d", &n, &m);

    int i, j;
    for (i = 1; i <= n; ++i)
        scanf("%d", &grid[i]);

    int num;
    for (i = 0; i < m; ++i)
    {
        scanf("%d", &num);
        cards[num]++;
    }

    dfs_play(cards[1], cards[2], cards[3], cards[4], 1);
    printf("%d", dp[cards[1]][cards[2]][cards[3]][cards[4]]);
    return 0;
}