// P1420 最长连号
// https://www.luogu.org/problemnew/show/P1420

#include <cstdio>
#include <algorithm>

using namespace std;

#define MAX_N 10000

int main()
{
    int n, i;
    int nums[MAX_N];
    scanf("%d", &n);
    for (i = 0; i < n; ++i)
        scanf("%d", &nums[i]);

    int ii = 0;  // following i
    int len = 0, maxLen = 0;
    for (i = 0; i < n; ++i) {
        if (nums[i] - i != nums[ii] - ii) 
        {
            maxLen = max(len, maxLen);
            ii = i;
            len = 0;
        }
        len++;
    }
    printf("%d", maxLen);
}