// P1590 失踪的7
// https://www.luogu.org/problemnew/show/P1590

#include <cstdio>

unsigned countNumbers(unsigned i, unsigned factor)
{
    return (i <= 7 ? i : i - 1) * factor - 1 + (i != 7);
}

int main()
{
    int t;
    unsigned int n, i, count, factor;
    scanf("%d", &t);
    t = 2;
    while (t--)
    {
        scanf("%u", &n);
        count = 0;
        factor = 1;
        while (n)
        {
            count += countNumbers(n % 10, factor);
            factor *= 9;
            n /= 10;
        }
        printf("%u\n", count);
    }
}