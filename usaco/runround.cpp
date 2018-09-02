/*
ID: yesimim1
TASK: runround
LANG: C++

#include <cstdio>

#include <fstream>
    ofstream fout ("runround.out");
    ifstream fin ("runround.in");
*/

#include <cstdio>
#include <cstring>

typedef unsigned int uint32_t;

const int MAX_D = 10;
const uint32_t MAX_INT = 0xffffffff;

FILE *fin = fopen("runround.in", "r");
FILE *fout = fopen("runround.out", "w");

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
            // fprintf(fout, "%lld\n", num);
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
            // fprintf(fout, "%d: %d: ", d, cur);
            // for (int i = 0; i < len; ++i)
            //     putchar('0' + solution[i]);
            // fprintf(fout, "\n");
            dfs((cur + x) % len, d + 1, len);
            solution[cur] = 0;
            used[x] = false;
        }
    }
}

int main()
{
    fscanf(fin, "%u", &start);

    int n, t;
    for (t = start, n = 0; t; t /= 10, ++n);

    used[0] = true;  // do not use 0;
    for (; n <= 9 && answer == MAX_INT; ++n)
        dfs(0, 0, n);
    fprintf(fout, "%u\n", answer);
    return 0;
}
