// P2550 [AHOI2001]彩票摇奖
// https://www.luogu.org/problemnew/show/P2550

#include <cstdio>

using namespace std;

#define MAX_N 35
#define NUM_BALLS 7

int main()
{
    int t, num;
    int prize[NUM_BALLS] = { 0 };
    bool balls[MAX_N] = { false };

    scanf("%d", &t);

    for (int i = 0; i < NUM_BALLS; ++i)
    {
        scanf("%d", &num);
        balls[num] = 1;
    }
    while (t--)
    {
        int count = NUM_BALLS;
        for (int i = 0; i < NUM_BALLS; ++i)
        {
            scanf("%d", &num);
            if (balls[num]) count--;
        }
        prize[count]++;
    }

    for (int i = 0; i < NUM_BALLS; ++i)
        printf("%d ", prize[i]);
}