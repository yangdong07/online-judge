// P1296 奶牛的耳语
// https://www.luogu.org/problemnew/show/P1296

#include <cstdio>
#include <algorithm>

using namespace std;

#define MAX_N 1000001

int main()
{
    int n, d;
    int pos[MAX_N];
    scanf("%d %d", &n, &d);
    for (int i = 0; i < n; ++i)
        scanf("%d", &pos[i]);

    sort(pos, pos + n);

    int i = 0, j = 1, count = 0;
    while (j < n)
    {
        if (pos[i] + d >= pos[j]) {
            j++;
        } else {
            count += (j - i - 1);
            i++;
        }
    }
    for ( ; i < j; ++i)
        count += (j - i - 1);
    printf("%d", count);
}