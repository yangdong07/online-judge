// P1563 玩具谜题
// https://www.luogu.org/problemnew/show/P1563


#include <cstdio>

#define MAX_N  100001
#define MAX_M  100001

int main()
{
    int n, m;
    int i, j;    // i for roles, j for instructions
    scanf("%d %d", &n, &m);

    char role[MAX_N][12];  // role for each guy
    int direction[MAX_N];  // 0 for inside, 1 for outside
    for (i = 0; i < n; ++i)
        scanf("%d %s", &direction[i], role[i]);
    
    int lr;     // 0 for left, 1 for right
    int count;  // count x man on left/right
    for (i = 0, j = 0; j < m; ++j)
    {
        scanf("%d %d", &lr, &count);
        // counter clockwise
        // inside/left - , inside/right +, 
        // outside/left +, outside/right -,
        if (direction[i] ^ lr)
            i = (i + count) % n;
        else
            i = (n + i - count) % n;   // 0 <= count < n;
    }
    printf("%s", role[i]);

}