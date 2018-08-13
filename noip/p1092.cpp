// P1092 虫食算
// https://www.luogu.org/problemnew/show/P1092

#include <cstdio>

const int MAX_N = 30;
int n;
char a[MAX_N], b[MAX_N], c[MAX_N];
bool used[MAX_N] = { false };    // mark used
int v[MAX_N] = { -1 };   // value of A,B,C .... Z

bool check_valid()
{
    // a[0] + b[0] >= n
    if (v[a[0]] + v[b[0]] >= n) return false;

    // (a[i] + b[i]) % n != c[i]
    for (int i = 0; i < n; ++i)
        if (v[a[i]] != -1 && v[b[i]] != -1 && v[c[i]] != -1)
            if ((v[a[i]] + v[b[i]]) % n != v[c[i]] && (v[a[i]] + v[b[i]] + 1) % n != v[c[i]])
                return false;
    return true;
}

bool check_result()
{
    int carry = 0, x;
    for (int i = n - 1; i >= 0; --i)
    {
        x = v[a[i]] + v[b[i]] + carry;
        if (x % n != v[c[i]])
            return false;
        carry = x / n;
    }
    return true;
}

void print_solution()
{
    int i;
    for (i = 0; i < n; ++i)
        printf("%d:%s ", i, used[i] ? "used" : "");
    printf("\n");
    for (i = 0; i < n; ++i)
        printf("%c:%d ", i + 'A', v[i]);
    putchar('\n');
    for (i = 0; i < n; ++i)
        putchar(v[a[i]] == -1 ? a[i] + 'A' : v[a[i]] + '0');
    putchar('\n');
    for (i = 0; i < n; ++i)
        putchar(v[b[i]] == -1 ? b[i] + 'A' : v[b[i]] + '0');
    putchar('\n');
    for (i = 0; i < n; ++i)
        putchar(v[c[i]] == -1 ? c[i] + 'A' : v[c[i]] + '0');
    putchar('\n');
    putchar('\n');
}

bool dfs(int d)
{

    if (d == n)
    {
        // print_solution();
        return check_result();
    }
    else if (d > 2 && !check_valid())
        return false;

    // if (d == n)
    // {
    //     printf("\n");
    //     return false;
    // }

    // printf("%d:%d ", d, x);
    for (int i = 0; i < n; ++i)
    {
        if (!used[i])
        {
            v[d] = i;
            used[i] = true;
            if (dfs(d + 1)) return true;
            used[i] = false;
            v[d] = -1;
        }
    }
    return false;
}


int main()
{
    scanf("%d", &n);
    scanf("%s\n%s\n%s", a, b, c);

    for (int i = 0; i < n; ++i)
    {
        v[i] = -1;
        used[i] = false;
        a[i] -= 'A';
        b[i] -= 'A';
        c[i] -= 'A';
    }
    // print_solution();

    // for (int i = 0; i < n; ++i)
    //     printf("%d:%d ", a[i], v[a[i]]);

    dfs(0);

    for (int i = 0; i < n; ++i)
        printf("%d ", v[i]);

    return 0;
}