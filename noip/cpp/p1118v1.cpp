// P1118 [USACO06FEB]数字三角形`Backward Digit Su`…
// https://www.luogu.org/problemnew/show/P1118

#include <cstdio>

const int MAX_N = 11;
int n, sum;

bool used[MAX_N] = { false };
int permutation[MAX_N];
int combination[MAX_N];

void print_solution()
{
    for (int i = 1; i <= n; ++i)
        printf("%d ", permutation[i]);
    printf("\n");
}

bool dfs(int k, int rest)
{
    // printf("%d %d\n", k, rest);
    // print_solution();
    // printf("\n");
    if (rest < 0) return false;
    if (k == n + 1) return rest == 0;
    // if (k > 3) return false;

    for (int x = 1; x <= n; ++x)
    {
        if (!used[x])
        {
            used[x] = true;
            permutation[k] = x;
            if (dfs(k + 1, rest - x * combination[k])) return true;
            used[x] = false;
        }
    }
    return false;
}

int main(void)
{
    scanf("%d %d", &n, &sum);

    // Combination[k] = C(n - 1, k - 1)
    combination[1] = 1;
    for (int k = 2; k <= n; ++k)
        combination[k] = combination[k - 1] * (n - k + 1) / (k - 1);

    // for (int i = 1; i <= n; ++i)
    //     printf("%d ", combination[i]);

    if (dfs(1, sum))
        print_solution();

    return 0;
}