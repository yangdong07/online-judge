
// P2404 自然数的拆分问题
// https://www.luogu.org/problemnew/show/P2404

#include <cstdio>

const int MAX_N = 8;

int target;
int a[MAX_N];

void print_sum(int n)
{
    printf("%d", a[0]);
    for (int i = 1; i < n; ++i)
        printf("+%d", a[i]);
    printf("\n");
}

void dfs(int cur, int n, int sum)
{
    if (sum == target)
    {
        print_sum(n);
        return;
    }
    else if (sum > target)
        return;
    
    for (int i = cur; i < target; ++i)
    {
        a[n] = i;
        dfs(i, n + 1, sum + i);
    }
}

int main()
{
    scanf("%d", &target);
    dfs(1, 0, 0);
    return 0;
}