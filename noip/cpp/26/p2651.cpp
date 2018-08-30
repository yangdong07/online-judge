// P2651 添加括号III
// https://www.luogu.org/problemnew/show/P2651

#include <cstdio>

int gcd(int a, int b)
{
  if (a == 0) return b;
  return gcd(b % a, a);
}

int main()
{
    int t, n, i;
    int a, b, c;  // for the numbers;
    scanf("%d", &t);
    while (t--)
    {
        scanf("%d", &n);
        scanf("%d %d", &a, &b);
        b = b / gcd(a, b);
        for (i = 2; i < n; ++i)
        {
            scanf("%d", &c);
            b = b / gcd(b, c);
        }
        printf(b == 1 ? "Yes\n" : "No\n");
    }
}