// P2676 超级书架
// https://www.luogu.org/problemnew/show/P2676

#include <cstdio>
#include <algorithm>

using namespace std;

#define MAX_N 20001

int main()
{
    int n, b, i;
    int h[MAX_N];  // heights
    scanf("%d %d", &n, &b);
    for (i = 0; i < n; ++i)
        scanf("%d", &h[i]);
    
    sort(h, h + n);

    int height = 0;
    for (i = n - 1; i >= 0; --i)
    {
        height += h[i];
        if (height >= b)
            break;
    }
    printf("%d", n - i);

}