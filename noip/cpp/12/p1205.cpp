
// P1205 [USACO1.2]方块转换 Transformations
// https://www.luogu.org/problemnew/show/P1205


#include <cstdio>

const int MAX_N = 11;
char a[MAX_N][MAX_N];
char b[MAX_N][MAX_N];

int n;

bool match_rotate_90()
{
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (b[j][n - i - 1] != a[i][j]) return false;
    return true;
}

bool match_rotate_180()
{
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (b[n - i - 1][n - j - 1] != a[i][j]) return false;
    return true;
}

bool match_rotate_270()
{
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (b[n - j - 1][i] != a[i][j]) return false;
    return true;
}

bool match_reflect()
{
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (b[i][n - j - 1] != a[i][j]) return false;
    return true;
}

bool match_reflect_rotate_90()
{
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (b[n - j - 1][n - i - 1] != a[i][j]) return false;
    return true;
}

bool match_reflect_rotate_180()
{
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (b[n - i - 1][j] != a[i][j]) return false;
    return true;
}

bool match_reflect_rotate_270()
{
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (b[j][i] != a[i][j]) return false;
    return true;
}

bool match_origin()
{
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (b[i][j] != a[i][j]) return false;
    return true;
}


int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
        scanf("%s", a[i]);
    for (int i = 0; i < n; ++i)
        scanf("%s", b[i]);
    
    if (match_rotate_90())
        printf("1");
    else if (match_rotate_180())
        printf("2");
    else if (match_rotate_270())
        printf("3");
    else if (match_reflect())
        printf("4");
    else if (match_reflect_rotate_90() || match_reflect_rotate_180() || match_reflect_rotate_270())
        printf("5");
    else if (match_origin())
        printf("6");
    else
        printf("7");
    
    printf("\n");
    
    return 0;
}