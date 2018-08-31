
// P1203 [USACO1.1]坏掉的项链Broken Necklace
// https://www.luogu.org/problemnew/show/P1203

#include <cstdio>

int max(int a, int b) { return a > b ? a : b; }

int main()
{
    const int MAX_N = 360 * 2;
    char necklace[MAX_N];
    int n, i;
    scanf("%d%s", &n, necklace + 1);
    for (i = 1; i <= n; ++i)
        necklace[i + n] = necklace[i];

    int rl[MAX_N] = {0}, bl[MAX_N] = {0};  // seen to left
    int rr[MAX_N] = {0}, br[MAX_N] = {0};  // seen to right

    for (i = 1; i <= n * 2; ++i)
    {
        if (necklace[i] == 'b')
        {
            bl[i] = bl[i - 1] + 1;
            rl[i] = 0;
        }
        else if (necklace[i] == 'r')
        {
            bl[i] = 0;
            rl[i] = rl[i - 1] + 1;
        }
        else
        {
            rl[i] = rl[i - 1] + 1;
            bl[i] = bl[i - 1] + 1;
        }
    }
    for (i = 2 * n; i >= 1; --i)
    {
        if (necklace[i] == 'b')
        {
            br[i] = br[i + 1] + 1;
            rr[i] = 0;
        }
        else if (necklace[i] == 'r')
        {
            br[i] = 0;
            rr[i] = rr[i + 1] + 1;
        }
        else
        {
            rr[i] = rr[i + 1] + 1;
            br[i] = br[i + 1] + 1;
        }
    }

    // for (i = 1; i <= 2 * n; ++i)
    //     printf("%c ", necklace[i]);
    // printf("\n");
    // for (i = 1; i <= 2 * n; ++i)
    //     printf("%-2d", rl[i]);
    // printf("\n");
    // for (i = 1; i <= 2 * n; ++i)
    //     printf("%-2d", bl[i]);
    // printf("\n");
    // for (i = 1; i <= 2 * n; ++i)
    //     printf("%-2d", rr[i]);
    // printf("\n");
    // for (i = 1; i <= 2 * n; ++i)
    //     printf("%-2d", br[i]);
    // printf("\n");

    int max_s = 0;
    for (i = 1; i < 2 * n; ++i)
        max_s = max(max_s, max(bl[i], rl[i]) + max(br[i + 1], rr[i + 1]));
    
    printf("%d\n", max_s < n ? max_s : n);


    return 0;
}