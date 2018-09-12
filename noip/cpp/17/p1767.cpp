
// P1767 家族_NOI导刊2010普及（10）
// https://www.luogu.org/problemnew/show/P1767


#include <cstdio>
#include <algorithm>
#include <cctype>

using namespace std;

const int MAX_N = 100;
const int MAX_M = 200;


int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};

int n, m;
int map[MAX_N][MAX_M] = {0};

void dfs(int x, int y)
{
    if (x < 0 || x >= n || y < 0 || y >= m)
        return;
    if (map[x][y] == 0) return;

    map[x][y] = 0; 
    for (int i = 0; i < 4; i++)
        dfs(x + dx[i], y + dy[i]);
}


int getcline(char *s)
{
    int i = 0;
    for (char c = getchar(); c != '\n' && c != EOF; c = getchar())
        s[i++] = c;
    s[i] = '\0';
    return i;
}


int main()
{
    scanf("%d", &n);
    while(getchar() != '\n');

    char s[MAX_M + 1];
    int i, j;
    m = 0;
    for (i = 0; i < n; i++)
    {
        int len = getcline(s);
        m = max(len, m);          
        for (j = 0; j < len; j++) 
            if (isalpha(s[j]))
                map[i][j] = 1; 
    }

    int ans = 0;
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            if (map[i][j])
                dfs(i, j), ans++;
    printf("%d", ans);
    return 0;
}