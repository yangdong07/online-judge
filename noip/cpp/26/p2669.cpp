// P2669 金币
// https://www.luogu.org/problemnew/show/P2669

#include <cstdio>

int main()
{
    int D, d = 0;
    scanf("%d", &D);

    int salary = 0, n = 1;
    while (true)
    {
        if (d + n > D)
        {
            salary += (D - d) * n;
            break;
        }
        else
        {
            salary += n * n;
            d += n;
            n += 1;
        }
    }

    printf("%d", salary);
}