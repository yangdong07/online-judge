// P1151 子数整数
// https://www.luogu.org/problemnew/show/P1151

#include <cstdio>

int main()
{
    int k, a1, a2, a3;
    scanf("%d", &k);

    bool noResult = true;

    for (int n = 10000; n <= 30000; n++)
    {
        if (n / 100 % k == 0
            && n / 10 % 1000 % k == 0
            && n % 1000 % k == 0) {
            if (noResult) {
                printf("%d", n);
                noResult = false;
            } else {
                printf("\n%d", n);
            }
        }
    }
    if (noResult) printf("No");
}