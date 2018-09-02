/*
ID: yesimim1
TASK: ariprog
LANG: C++

#include <cstdio>

#include <fstream>
    ofstream fout ("ariprog.out");
    ifstream fin ("ariprog.in");
*/

#include <cstdio>
#include <algorithm>
#include <cstring>

const int MAX_N = 250 * 250 * 2 + 1;
const int MAX_M = 250 * 249 / 2 + 1;
const int MAX_I = 10001;

struct item
{
    int a, b;
    // item(int a, int b): a(a), b(b) {}
};

bool cmp(item &a, item &b)
{
    if (a.b != b.b)
        return a.b < b. b;
    return a.a < b.a;
}

bool is_bisquares[MAX_N];
int bisquares[MAX_M];
item items[MAX_I];
int n, m;

bool is_bisquares_progression(int a, int b)
{
    for (int i = a + b, k = 1; k < n; i += b, ++k)
        if (!is_bisquares[i]) return false;
    return true;
}

int main()
{
    FILE *fin = fopen ("ariprog.in", "r");
    FILE *fout = fopen ("ariprog.out", "w");

    int i, j, k;
    fscanf(fin, "%d%d", &n, &m);
    memset(is_bisquares, false, sizeof(is_bisquares));
    k = 0;
    for (i = 0; i <= m; i++)
        for (j = i; j <= m; j++)
            if (!is_bisquares[i * i + j * j])
            {
                bisquares[k++] = i * i + j * j;
                is_bisquares[i * i + j * j] = true;
            }
    // fprintf(fout, "%d\n", k);
    std::sort(bisquares, bisquares + k);

    int a, b;
    int solutions = 0;
    int max_a = bisquares[k - 1];
    for (i = 0; i < k; ++i)
    {
        a = bisquares[i];
        for (j = i + 1; j < k; ++j)
        {
            b = bisquares[j] - a;
            if (a + (n - 1) * b > max_a) break;
            if (is_bisquares_progression(a, b))
            {
                items[solutions].a = a;
                items[solutions].b = b;
                // fprintf(fout, "%d %d\n", a, b);
                ++solutions;
            }
        }
    }
    if (!solutions)
    {
        fprintf(fout, "NONE\n");
        return 0;
    }

    std::sort(items, items + solutions, cmp);
    for (i = 0; i < solutions; ++i)
        fprintf(fout, "%d %d\n", items[i].a, items[i].b);

    return 0;
}