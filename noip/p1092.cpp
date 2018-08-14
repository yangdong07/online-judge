// P1092 虫食算
// https://www.luogu.org/problemnew/show/P1092

#include <cstdio>

const int MAX_N = 30;
int n;
char s[4][MAX_N];
bool used[MAX_N] = { false };    // mark used
int v[MAX_N] = { -1 };   // value of A,B,C .... Z

void print_solution()
{
    int i;
    for (i = 0; i < n; ++i)
        printf("%d:%s ", i, used[i] ? "used" : "");
    printf("\n");
    for (i = 0; i < n; ++i)
        printf("%c:%d ", i + 'A', v[i]);
    putchar('\n');

    for (int r = 0; r < 3; ++r)
    {
        for (i = 0; i < n; ++i)
            putchar(v[s[r][i]] == -1 ? s[r][i] + 'A' : v[s[r][i]] + '0');
        putchar('\n');
    }
    putchar('\n');
}

bool solve(int r, int c, int sum)
{
    if (c == n)
    {
        // print_solution();
        return sum == 0;
    }
    int j = n - c - 1;

    int x = v[s[r][j]], ch = s[r][j];
    if (r < 2)  // rows
    {
        if (x != -1) // assigned
            return solve(r + 1, c, sum + x);

        for (int z = n - 1; z >= 0; --z)
        {
            if (!used[z])
            {
                v[ch] = z;
                used[z] = true;
                if (solve(r + 1, c, sum + z))
                    return true;
                used[z] = false;
                v[ch] = -1;
            }
        }
    }
    else  // row of sum
    {
        int d = sum % n;
        if (x == d)    // assigned and match
            return solve(0, c + 1, sum / n);
        if (x != -1 && x != d)  // assigned and not match
            return false;
        if (x == -1 && used[d]) // not assigned and digit used
            return false;
        
        v[ch] = d;
        used[d] = true;
        if (solve(0, c + 1, sum / n)) return true;
        used[d] = false;
        v[ch] = -1;
        return false;
    }
    return false;
}

int main()
{
    scanf("%d", &n);
    scanf("%s\n%s\n%s", s[0], s[1], s[2]);

    // for (int i = 0; i < n; ++i)
    //     printf("%d:%d ", a[i], v[a[i]]);


    for (int i = n - 1, j = 0; i >= 0; --i)
    {
        v[i] = -1;
        used[i] = false;
        for (int r = 0; r < 3; ++r)
            s[r][i] -= 'A';
    }

    solve(0, 0, 0);

    for (int i = 0; i < n; ++i)
        printf("%d ", v[i]);

    return 0;
}