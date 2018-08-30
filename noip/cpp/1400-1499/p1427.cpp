// P1427 小鱼的数字游戏
// https://www.luogu.org/problemnew/show/P1427

#include <cstdio>

#define MAX_N 100

int main()
{
    int memory[MAX_N], i = 0, n;

    while (1) {
        scanf("%d", &n);
        if (n == 0) break;
        memory[i++] = n;
    }
    printf("%d", memory[--i]);
    while (i > 0)
        printf(" %d", memory[--i]);

}