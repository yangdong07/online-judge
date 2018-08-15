#include <cstdio>

const int MAX_N = 12;
int n, sum;
int permutation[MAX_N];
int combination[MAX_N];


void swap(int i, int j)
{
    int t = permutation[i];
    permutation[i] = permutation[j];
    permutation[j] = t;
}


bool dfs(int k, int rest)
{
    if (rest < 0) return false;
    if (k > n)
        return rest == 0;

    for (int i = k; i <= n; i++)
    {
        swap(i, k);
        if (dfs(k + 1, rest - permutation[k] * combination[k])) return true;
        swap(i, k);
    }
    return false;
}

int main()
{
    scanf("%d%d", &n, &sum);
    int i, j;
    combination[1] = 1;
    for (i = 1; i <= n; i++)
    {
        for (j = i; j > 1; j--)
            combination[j] += combination[j - 1];
        permutation[i] = i;
    }

    if (dfs(1, sum))
    {
        for (i = 1; i <= n / 2; i++)
            if (permutation[i] > permutation[n - i + 1])
                swap(i, n - i + 1);
        for (i = 1; i <= n; i++)
            printf("%d ", permutation[i]);
    }
    return 0;
}