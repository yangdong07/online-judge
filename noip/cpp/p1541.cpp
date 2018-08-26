// P1541 乌龟棋
// https://www.luogu.org/problemnew/show/P1541

#include <cstdio>

int max(int a, int b) { return a > b ? a : b; }

/* solution2 */

const int MAX_N = 351;
const int MAX_M = 41;

int dp[MAX_M][MAX_M][MAX_M] = {0};

int main()
{
    int n, m, i;
    scanf("%d%d", &n, &m);

    int grid[MAX_N];
    for (i = 1; i <= n; ++i) scanf("%d", &grid[i]);

    int step, cards[5] = {0};
    for (i = 0; i < m; ++i)
    {
        scanf("%d", &step);
        cards[step]++;
    }

    int c1, c2, c3, c4;
    int max_s;
    for (c1 = 0; c1 <= cards[1]; ++c1)
        for (c2 = 0; c2 <= cards[2]; ++c2)
            for (c3 = 0; c3 <= cards[3]; ++c3)
                for (c4 = 0; c4 <= cards[4]; ++c4)
                {
                    max_s = dp[c2][c3][c4]; //  = dp[c1 - 1][c2][c3][c4];
                    if (c2) max_s = max(max_s, dp[c2 - 1][c3][c4]);  // = dp[c1][c2-1][c3][c4]
                    if (c3) max_s = max(max_s, dp[c2][c3 - 1][c4]);
                    if (c4) max_s = max(max_s, dp[c2][c3][c4 - 1]);
                    dp[c2][c3][c4] = max_s + grid[1 + c1 + (c2 << 1) + c3 * 3 + (c4 << 2)];
                }
    printf("%d", dp[cards[2]][cards[3]][cards[4]]);
    return 0;
}





/* solution1, dfs + memory */

// int n, m;
// int grid[MAX_N];
// int cards[5] = {0, 0, 0, 0, 0}; // cards

// int dp[MAX_M][MAX_M][MAX_M][MAX_M] = {0}; //!!!

// int dfs_play(int a, int b, int c, int d, int step)
// {
//     if (step == n)
//         return grid[step];
//     if (dp[a][b][c][d]) return dp[a][b][c][d];

//     int max_s = 0;

//     if (a > 0)
//         max_s = max(max_s, dfs_play(a - 1, b, c, d, step + 1));
//     if (b > 0)
//         max_s = max(max_s, dfs_play(a, b - 1, c, d, step + 2));
//     if (c > 0)
//         max_s = max(max_s, dfs_play(a, b, c - 1, d, step + 3));
//     if (d > 0)
//         max_s = max(max_s, dfs_play(a, b, c, d - 1, step + 4));
    
//     return dp[a][b][c][d] = max_s + grid[step];
// }

// int main()
// {
//     scanf("%d %d", &n, &m);

//     int i, j;
//     for (i = 1; i <= n; ++i)
//         scanf("%d", &grid[i]);

//     int num;
//     for (i = 0; i < m; ++i)
//     {
//         scanf("%d", &num);
//         cards[num]++;
//     }

//     dfs_play(cards[1], cards[2], cards[3], cards[4], 1);
//     printf("%d", dp[cards[1]][cards[2]][cards[3]][cards[4]]);
//     return 0;
// }