// P1182 数列分段`Section II`
// https://www.luogu.org/problemnew/show/P1182



#include <cstdio>
#include <algorithm>

using namespace std;

const int MAX_N = 100001;
int acc[MAX_N]; // accumulate sum
int n, m;

bool try_divide(int max_sum)
{
    // try divide acc to m sections, limit sum <= max_sum 
    // return: false: sections > m, sholud enlarge max_sum to make less sections
    //         true: sections <= m, should reduce max_sum to make more sections
    // printf("try divide to %d segments, sum <= %d to\n", m, max_sum);
    int start = acc[0];
    int sections = 1;
    for (int i = 1; i < n; ++i)
    {
        if (acc[i + 1] - start > max_sum)
        {
            // printf("%d: %d, %d\n", start, acc[i], sections);
            start = acc[i];
            sections++;
            if (sections > m) return false;
        }
    }
    return sections <= m;
}

int binary_search(int low, int high)
{
    if (low >= high) return low;

    int mid = (low + high) / 2;

    if (try_divide(mid))
        return binary_search(low, mid);
    else
        return binary_search(mid + 1, high);
}

int main()
{

    scanf("%d %d", &n, &m);

    int max_num = 0, tmp;

    acc[0] = 0;
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &tmp);
        max_num = max(max_num, tmp);
        acc[i] = acc[i - 1] + tmp;
    }

    // for (int i = 1; i <= n; ++i)
    //     printf("%d: %d\n", max_num, acc[i]);

    printf("%d", binary_search(max_num, acc[n]));

    return 0;
}