
// P1473 零的数列 Zero Sum
// https://www.luogu.org/problemnew/show/P1473

#include <cstdio>

int evaluate(char *s)
{
    int a = 0, b = 0;
    char op = '+';  // default
    for (char *p = s; *p; ++p)
    {
        if (*p == '+' || *p == '-')
        {
            if (op == '+') a += b;
            else if (op == '-') a -= b;
            op = *p;
            b = 0;
        }
        else if ('0' <= *p && *p <= '9')
            b = b * 10 + *p - '0';
    }
    if (op == '+') a += b;
    else if (op == '-') a -= b;
    return a;
}

void dfs(char s[], int i, int n)
{
    if (i >= n)
    {
        if (evaluate(s) == 0)
            printf("%s\n", s);
        return;
    }
    for (int k = 0; k < 3; ++k)
    {
        s[i] = " +-"[k];
        dfs(s, i + 2, n);
    }
}

int main()
{
    const int MAX_N = 20;
    int n, i;
    char s[MAX_N];
    scanf("%d", &n);

    for (i = 0; i < n; ++i)
        s[i * 2] = '1' + i;
    
    s[2 * n - 1] = '\0';
    
    dfs(s, 1, 2 * n - 1);
    
    return 0;
}