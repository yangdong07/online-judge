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
    if (permutation[1] > permutation[n])
        for (int i = n; i >= 1; --i)
            printf("%d ", permutation[i]);
    else
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
    if (k == 0) return rest == 0;


    for (int x = n; x > 0; --x)
    {
        if (!used[x])
        {
            used[x] = true;
            permutation[k] = x;
            rest -= x * combination[k];
            for (int y = n; y > 0; --y)
            {
                if (!used[y])
                {
                    used[y] = true;
                    permutation[n - k + 1] = y;
                    if (dfs(k - 1, rest - y * combination[k])) return true;
                    used[y] = false;
                }
            }
            rest += x * combination[k];
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

    if (n & 1)
    {
        for (int x = n; x > 0; --x)
        {
            used[x] = true;
            permutation[n / 2 + 1] = x;
            if (dfs(n / 2, sum - combination[n / 2 + 1] * x))
            {
                print_solution();
                return 0;
            }
            used[x] = false;
        }
    }
    else
    {
        if (dfs(n / 2, sum))
        {
            print_solution();
            return 0;
        }
    }
    return 0;
}