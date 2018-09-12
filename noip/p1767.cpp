
// P1767 家族_NOI导刊2010普及（10）
// https://www.luogu.org/problemnew/show/P1767

#include <cstdio>
#include <cstring>
#include <cctype>

const int MAX_N = 110;
const int MAX_M = 210;

int dx[] = {0, 1, 0, -1};
int dy[] = {1, 0, -1, 0};

int n;
char map[MAX_N][MAX_M + 1] = {0};
int color[MAX_N][MAX_M] = {0};

int getline(char *s)
{
    int i = 0;
    for (char c = getchar(); c != '\n' && c != EOF; c = getchar())
        s[i++] = c;
    s[i] = '\0';
    return i;
}

void dfs(int x, int y, int id)
{
    if (x < 0 || x >= n || y < 0 || map[x][y] == '\0')
        return;
    if (map[x][y] == ' ' || map[x][y] == '*' || color[x][y])
        return;
    color[x][y] = id;
    for (int i = 0; i < 4; ++i)
        dfs(x + dx[i], y + dy[i], id);
}

int main()
{
    int i, j;
    scanf("%d\n", &n);

    for (i = 0; i < n; ++i)
        getline(map[i]);

    int id = 0;
    for (i = 0; i < n; ++i)
        for (j = 0; j < strlen(map[i]); ++j)
            if (isalpha(map[i][j]) && !color[i][j])
                dfs(i, j, ++id);
    
    // for (i = 0; i < n; ++i)
    //     printf("%s", map[i]);

    printf("%d", id);

    return 0;
}