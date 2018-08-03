// P2666 Bessie的秘密牧场
// https://www.luogu.org/problemnew/show/P2666

#include <cstdio>

using namespace std;

#define MAX_N 101
#define MAX_NN 10001

bool isSquare[MAX_NN] = { false };

void init()
{
    for (int i = 0; i <= 100; ++i)
        isSquare[i * i] = true;
}

int answer;
void dfs(int remain, int depth)
{
    // printf("%d %d\n", depth, remain);
    if (depth == 3)
    {
        if (isSquare[remain]) answer++;
        return;
    }
    for (int i = 0; i <= 100; ++i)
    {
        if (remain < i * i) break;
        dfs(remain - i * i, depth + 1);
    }
}

int main()
{
    init();

    int n;
    scanf("%d", &n);

    answer = 0;
    dfs(n, 0);
    printf("%d", answer);
}