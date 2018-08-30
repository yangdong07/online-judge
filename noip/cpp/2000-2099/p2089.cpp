// P2089 烤鸡
// https://www.luogu.org/problemnew/show/P2089

#include <cstdio>

#define NUM 10

int a[NUM] = { 0 };

bool print = false;

int dfs(int i, int n)
{
    if (n < 0)
        return 0;
    
    if (i == NUM)
    {
        if (n == 0)
        {
            if (print)
            {
                for (int j = 0; j < NUM; ++j)
                    printf("%d ", a[j]);
                printf("\n");
            }
            return 1;
        }
        else return 0;
    }

    int count = 0;
    for (int j = 1; j <= 3; ++j)
    {
        a[i] = j;
        count += dfs(i + 1, n - j);
    }

    return count;
}

int main()
{
    int n;

    scanf("%d", &n);
    if (n < 10 || n > 30)
    {
        printf("0");
        return 0;
    }

    print = false;
    printf("%d\n", dfs(0, n));
    print = true;
    dfs(0, n);

}
