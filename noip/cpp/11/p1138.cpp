// P1138 第k小整数
// https://www.luogu.org/problemnew/show/P1138

#include <cstdio>
#include <algorithm>

using namespace std;

#define MAX_N 10000

int main()
{
    int n, k, nums[MAX_N];
    scanf("%d %d", &n, &k);
    for (int i = 0; i < n; ++i)
        scanf("%d", &nums[i]);
    sort(nums, nums + n);
    
    // find k
    int ii = 0;  // follow i
    for (int i = 1; i < n; ++i)
    {
        if (nums[i] != nums[ii])
        {
            nums[++ii] = nums[i];
            if (ii == k - 1) 
            {
                printf("%d", nums[ii]);
                return 0;
            }
        }
    }
    printf("NO RESULT");
}