// P1316 丢瓶盖
// https://www.luogu.org/problemnew/show/P1316

#include <cstdio>
#include <algorithm>

using namespace std;

const int MAX_N = 100001;
int x[MAX_N]; // x position
int n, m;  // select m from n

bool greedy_select(int min_distance)
{
    // greedy select x as more as possible, 
    // the distance from selected to prev is just greater than min_distance
    // return: true: selects >= m, sholud enlarge min_distance to make less selects
    //         false: selects < m, should reduce min_distance to make more selects
    // printf("try select %d with min_distance larger than %d\n", m, min_distance);
    int prev = x[0];
    int selects = 1;   // first
    for (int i = 1; i < n; ++i)
    {
        if (x[i] - prev >= min_distance)
        {
            prev = x[i];
            selects++;
            if (selects >= m) return true;
        }
    }
    return selects >= m;
}

int binary_search(int low, int high)
{
    int l = low, r = high, mid;

    while (l < r)
    {
        mid = (l + r + 1) / 2;
        if (greedy_select(mid))
            l = mid;
        else
            r = mid - 1;
    }
    return l;
}

int main()
{
    scanf("%d %d", &n, &m);

    for (int i = 0; i < n; ++i)
        scanf("%d", &x[i]);

    sort(x, x + n);

    printf("%d", binary_search(1, x[n - 1] - x[0]));

    return 0;
}