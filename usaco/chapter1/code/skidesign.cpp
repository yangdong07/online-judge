/*
ID: yesimim1
TASK: skidesign
LANG: C++

#include <cstdio>
    FILE *fin = fopen ("skidesign.in", "r");
    FILE *fout = fopen ("skidesign.out", "w");

#include <fstream>
    ofstream fout ("skidesign.out");
    ifstream fin ("skidesign.in");
*/

#include <cstdio>
#include <algorithm>

int main()
{
    FILE *fin = fopen("skidesign.in", "r");
    FILE *fout = fopen("skidesign.out", "w");

    const int MAX_N = 1001;
    const int MIN_H = 17;
    int n, i;
    int heights[MAX_N];
    fscanf(fin, "%d", &n);
    for (i = 0; i < n; ++i)
        fscanf(fin, "%d", &heights[i]);
    
    std::sort(heights, heights + n);

    int lower = heights[0], higher = heights[n - 1];

    int l, h, cost, min_cost = (1 << 30);
    for (l = lower; l <= higher - MIN_H; ++l)
    {
        cost = 0;
        h = l + MIN_H;
        for (i = 0; heights[i] < l; ++i)
            cost += (l - heights[i]) * (l - heights[i]);
        for (i = n - 1; heights[i] > h; --i)
            cost += (h - heights[i]) * (h - heights[i]);
        min_cost = std::min(min_cost, cost);
    }

    fprintf(fout, "%d\n", min_cost);
    return 0;
}