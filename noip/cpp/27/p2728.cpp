
// P2728 纺车的轮子 Spinning Wheels
// https://www.luogu.org/problemnew/show/P2728

#include <cstdio>
#include <cstring>

const int CYCLE = 360;
const int N_WHEELS = 5;

struct Wedge
{
    int begin, span;

    void mark(int m[], int angle)
    {
        for (int i = begin; i <= begin + span; ++i)
                ++m[(i + angle) % CYCLE];
    }
};

struct Wheel
{
    int angle;
    int speed;
    int n_wedges;
    Wedge wedges[5];
    void spin()
    {
        angle += speed;
    }
    void mark(int m[])
    {
        for (int i = 0; i < n_wedges; ++i)
            wedges[i].mark(m, angle);
    }
};

int main()
{
    int i, j;
    Wheel wheels[N_WHEELS];

    for (i = 0; i < N_WHEELS; ++i)
    {
        wheels[i].angle = 0;
        scanf("%d %d", &wheels[i].speed, &wheels[i].n_wedges);
        for (j = 0; j < wheels[i].n_wedges; ++j)
            scanf("%d %d", &wheels[i].wedges[j].begin, &wheels[i].wedges[j].span);
    }

    int mark[CYCLE];
    for (int t = 0; t < CYCLE; ++t)
    {
        memset(mark, 0, sizeof(mark));
        for (i = 0; i < N_WHEELS; ++i)
            wheels[i].mark(mark);
        
        for (i = 0; i < CYCLE; ++i)
            if (mark[i] == N_WHEELS)
            {
                printf("%d\n", t);
                return 0;
            }
        
        for (i = 0; i < N_WHEELS; ++i)
            wheels[i].spin();
    }
    printf("none\n");

    return 0;
}