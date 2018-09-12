/*
ID: yesimim1
TASK: spin
LANG: C++

#include <cstdio>
FILE *fin = fopen ("spin.in", "r");
FILE *fout = fopen ("spin.out", "w");

void _fputc(char c) { fputc(c, fout); }

#include <fstream>
    ofstream fout ("spin.out");
    ifstream fin ("spin.in");
*/

#include <cstdio>
#include <cstring>

const int CYCLE = 360;
const int N_WHEELS = 5;

FILE *fin = fopen ("spin.in", "r");
FILE *fout = fopen ("spin.out", "w");

void _fputc(char c) { fputc(c, fout); }


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
        fscanf(fin, "%d %d", &wheels[i].speed, &wheels[i].n_wedges);
        for (j = 0; j < wheels[i].n_wedges; ++j)
            fscanf(fin, "%d %d", &wheels[i].wedges[j].begin, &wheels[i].wedges[j].span);
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
                fprintf(fout, "%d\n", t);
                return 0;
            }
        
        for (i = 0; i < N_WHEELS; ++i)
            wheels[i].spin();
    }
    fprintf(fout, "none\n");

    return 0;
}