
// P2368 EXCEEDED WARNING B
// https://www.luogu.org/problemnew/show/P2368

#include <cstdio>
#include <vector>

using namespace std;

typedef long long INT64;

const INT64 tail = 987654321;

int main()
{
    // vector<int> nums[10];

    // nums[0].push_back(0);

    // vector<int>::iterator it;
    // int n;
    // for (int i = 1, base = 10; i < 10; ++i, base *= 10)
    // {
    //     for (int d = 0; d < 10; ++d)
    //         for (it = nums[i - 1].begin(); it != nums[i - 1].end(); ++it)
    //         {
    //             n = base / 10 * d + *it;
    //             if ((INT64)n * n % base == tail % base)
    //             {
    //                 // printf("%d %lld\n", n, (INT64)n * n);
    //                 nums[i].push_back(n);
    //             }
    //         }
    //     // printf("\n");
    // }

    int n;
    scanf("%d", &n);
    if (n < 9)
        printf("0\n");
    else if (n == 9)
        printf("8\n");
    else
    {
        printf("72");
        for (int i = 0; i < n - 10; i++)
            printf("0");
        printf("\n");
    }
    return 0;
}