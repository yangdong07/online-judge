// P1968 美元汇率
// https://www.luogu.org/problemnew/show/P1968

#include <cstdio>

double max(double a, double b) { return a > b ? a : b; }

int main()
{
    int n;
    scanf("%d", &n);

    double max_dollar = 100;
    double max_mark, max_t;
    int rate;
    scanf("%d", &rate);
    max_mark = max_dollar * rate;

    for (int i = 2; i <= n; ++i)
    {
        scanf("%d", &rate);
        max_t = max(max_dollar, max_mark / rate);
        max_mark = max(max_mark, max_dollar * rate);
        max_dollar = max_t;
    }

    printf("%.2lf", max_dollar);
    return 0;
}