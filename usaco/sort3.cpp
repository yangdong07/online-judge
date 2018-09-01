/*
ID: yesimim1
TASK: sort3
LANG: C++

#include <cstdio>
    FILE *fin = fopen ("sort3.in", "r");
    FILE *fout = fopen ("sort3.out", "w");

#include <fstream>
    ofstream fout ("sort3.out");
    ifstream fin ("sort3.in");
*/

#include <cstdio>

int min(int a, int b) { return a < b ? a : b; }

int main()
{
    FILE *fin = fopen ("sort3.in", "r");
    FILE *fout = fopen ("sort3.out", "w");

    const int MAX_N = 1001;
    int n, i, j;

    fscanf(fin, "%d", &n);
    
    int a[MAX_N], b[MAX_N];
    int mismatch[4][4] = {0};
    int count[4] = {0};
    for (i = 0; i < n; ++i)
    {
        fscanf(fin, "%d", &a[i]);
        count[a[i]]++;
    }
    j = 0;
    for (int k = 1; k <= 3; ++k)
        for (i = 0; i < count[k]; ++i)
            b[j++] = k;
    
    // for (i = 0; i < n; ++i)
    //     fprintf(fout, "%d ", a[i]);
    // fprintf(fout, "\n");
    // for (i = 0; i < n; ++i)
    //     fprintf(fout, "%d ", b[i]);
    // fprintf(fout, "\n");

    for (i = 0; i < n; ++i)
        mismatch[b[i]][a[i]]++;

    int swap = 0, sx, rest = 0;
    for (i = 1; i <= 3; ++i)
    {
        for (j = i + 1; j <= 3; ++j)
        {
            sx = min(mismatch[i][j], mismatch[j][i]); 
            swap += sx;
            mismatch[i][j] -= sx;
            mismatch[j][i] -= sx;
            rest += (mismatch[i][j] + mismatch[j][i]);
        }
    }
    fprintf(fout, "%d\n", swap + rest * 2 / 3);

    return 0;
}