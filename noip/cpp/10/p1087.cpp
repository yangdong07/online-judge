// P1087 FBI树
// https://www.luogu.org/problemnew/show/P1087

#include <cstdio>

const int MAX_N = 1030;

int n;
char s[MAX_N];

char search(int l, int r)
{
    char c;
    if (l == r)
    {
        c = s[l] == '0' ? 'B' : 'I';
        putchar(c);
        return c;
    }
    int m = (r + l) / 2;
    c = search(l, m);
    if (c == search(m + 1, r))
    {
        putchar(c);
        return c;
    }
    else
    {
        putchar('F');
        return 'F';
    }
}

int main()
{
    scanf("%d %s", &n, &s[1]);
    search(1, 1 << n);
    return 0;
}