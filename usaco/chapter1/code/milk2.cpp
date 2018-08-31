/*
ID: yesimim1
TASK: milk2
LANG: C++

#include <cstdio>
    FILE *fin = fopen ("milk2.in", "r");
    FILE *fout = fopen ("milk2.out", "w");

#include <fstream>
    ofstream fout ("milk2.out");
    ifstream fin ("milk2.in");
*/

#include <cstdio>
#include <algorithm>

using namespace std;

struct Range
{
    int left;
    int right;
};

bool cmp(Range &a, Range &b)
{
    return a.left < b.left;
}

int main()
{
    FILE *fin = fopen ("milk2.in", "r");
    FILE *fout = fopen ("milk2.out", "w");

    const int MAX_N = 5001;
    int n, i, j;
    Range range[MAX_N];
    fscanf(fin, "%d", &n);
    for (i = 0; i < n; i++)
        fscanf(fin, "%d %d", &range[i].left, &range[i].right);
    sort(range, range + n, cmp);

    for (i = 0, j = 1; j < n; j++)
    {
        // merge
        if (range[j].left <= range[i].right)
            range[i].right = max(range[i].right, range[j].right);
        else
        {
            i++;
            range[i].left = range[j].left;
            range[i].right = range[j].right;
        }
    }
    n = i + 1;
    int max0 = 0, max1 = range[0].right - range[0].left;
    for (i = 1; i < n; ++i)
    {
        max0 = max(max0, range[i].left - range[i - 1].right);
        max1 = max(max1, range[i].right - range[i].left);
    }
    fprintf(fout, "%d %d\n", max1, max0);

    return 0;
}