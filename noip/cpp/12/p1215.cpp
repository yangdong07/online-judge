
// P1215 [USACO1.4]母亲的牛奶 Mother's Milk
// https://www.luogu.org/problemnew/show/P1215

#include <cstdio>

const int MAX_N = 21;

bool v[MAX_N][MAX_N][MAX_N] = {false};

int A, B, C;   // capacity
bool status[MAX_N] = {false};  // all status of C

int min(int a, int b) { return a < b ? a : b; }

void dfs(int a, int b, int c)
{
    if (v[a][b][c]) return;
    v[a][b][c] = true;
    if (a == 0) status[c] = true;

    int d;
    // a to b
    d = min(a, B - b);
    if (d) dfs(a - d, b + d, c);
    // b to a
    d = min(A - a, b);
    if (d) dfs(a + d, b - d, c);
    // a to c
    d = min(a, C - c);
    if (d) dfs(a - d, b, c + d);
    // c to a
    d = min(A - a, c);
    if (d) dfs(a + d, b, c - d);
    // b to c
    d = min(b, C - c);
    if (d) dfs(a, b - d, c + d);
    // c to b
    d = min(B - b, c);
    if (d) dfs(a, b + d, c - d);
}

int main()
{
    scanf("%d %d %d", &A, &B, &C);
    dfs(0, 0, C);

    for (int i = 0; i <= C; ++i)
        if (status[i])
            printf("%d ", i);
    printf("\n");
    return 0;
}