// P1464 Function
// https://www.luogu.org/problemnew/show/P1464


#include <cstdio>

#define MAX_N 21

int w[MAX_N][MAX_N][MAX_N];
int m[MAX_N][MAX_N][MAX_N] = { false };

int f(int a, int b, int c)
{
    if (a <= 0 || b <= 0 || c <= 0) return 1;
    else if (a > 20 || b > 20 || c > 20) return f(20, 20, 20);

    if (m[a][b][c]) return w[a][b][c];

    int result;
    if (a < b && b < c)
        result = f(a, b, c - 1) + f(a, b - 1, c - 1) - f(a, b - 1, c);
    else
        result = f(a - 1, b, c) + f(a - 1, b - 1, c) + f(a - 1, b , c - 1) - f(a - 1, b - 1, c - 1);

    w[a][b][c] = result;
    m[a][b][c] = true;

    return result;
}

int main()
{
    int a, b, c;
    while (1)
    {
        scanf("%d %d %d", &a, &b, &c);
        if (a == -1 && b == -1 && c == -1)
            break;
        printf("w(%d, %d, %d) = %d\n", a, b, c, f(a, b, c));
    }
}