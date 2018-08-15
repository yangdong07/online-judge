// P3865 【模板】ST表
// https://www.luogu.org/problemnew/show/P3865

#include <cstdio>
#include <algorithm>
#include <cmath>

using namespace std;

const int MAX_N = 100005;
const int MAX_M = 21;

int n, m;
int st[MAX_N][MAX_M];
int lg[MAX_N];  // lg[i] = lg(i) + 1

void init_lg()
{
    lg[0] = 0;
    for (int i = 1; i <= n; ++i)
        lg[i] = lg[i - 1] + ((1 << lg[i - 1]) == i);

    // for (int i = 1; i <= n; ++i)
    //     printf("%d ", i);
    // printf("\n");
    // for (int i = 1; i <= n; ++i)
    //     printf("%d ", lg[i]);
    // printf("\n");
    // for (int i = 1; i <= n; ++i)
    //     printf("%d ", int(log2(i)));
    // printf("\n");
}

int query(int l, int r)
{
    int k = lg[r - l] - 1;
    // int k = log2(r - l + 1);
    // int d = (1 << (lg[r - l] - 1)) - 1;
    // printf("%d %d %d %d\n", l, r, k, (1 << k) - 1);
    // return 1;
    return max(st[l][k], st[r - (1 << k) + 1][k]);
}

int main()
{
    int i, j;
    scanf("%d %d", &n, &m);

    // pre-processing sparse table
    for (i = 1; i <= n; ++i)
        scanf("%d", &st[i][0]);

    for (j = 1; j < MAX_M; ++j)
        for (i = 1; (1 << (j - 1)) + i <= n; ++i)
            st[i][j] = max(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
        
    init_lg();

    int l, r;
    for (i = 0; i < m; ++i)
    {
        scanf("%d %d", &l, &r);
        printf("%d\n", query(l, r) + 1);
    }
    return 0;
}