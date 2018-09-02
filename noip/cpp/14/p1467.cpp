
// P1467 循环数 Runaround Numbers
// https://www.luogu.org/problemnew/show/P1467

#include <cstdio>
#include <cstring>

typedef unsigned int uint32_t;

const int MAX_D = 10;
const uint32_t MAX_INT = 0xffffffff;

uint32_t start;
uint32_t answer = MAX_INT;

int solution[MAX_D] = {0};
int used[10] = {false};  // used status

void dfs(int cur, int d, int len)
{
    if (d == len)
    {
        if (cur == 0) // return to the begining
        {
            uint32_t num = 0;
            for (int i = 0; i < len; ++i)
                num = num * 10 + solution[i];
            // printf("%lld\n", num);
            if (start < num && num < answer) answer = num;
        }
        return;
    }

    if (solution[cur]) return;

    for (int x = 1; x < 10; ++x)
    {
        if (!used[x])
        {
            used[x] = true;
            solution[cur] = x;
            // printf("%d: %d: ", d, cur);
            // for (int i = 0; i < len; ++i)
            //     putchar('0' + solution[i]);
            // printf("\n");
            dfs((cur + x) % len, d + 1, len);
            solution[cur] = 0;
            used[x] = false;
        }
    }
}

int main()
{
    scanf("%u", &start);

    int n, t;
    for (t = start, n = 0; t; t /= 10, ++n);

    used[0] = true;  // do not use 0;
    for (; n <= 9 && answer == MAX_INT; ++n)
        dfs(0, 0, n);
    printf("%u", answer);
    return 0;
}
