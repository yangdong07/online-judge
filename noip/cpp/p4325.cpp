// P4325 [COCI2006-2007#1] Modulo
// https://www.luogu.org/problemnew/show/P4325

#include <cstdio>

bool inArray(int a, int arr[], int l)
{
    for (int i = 0; i < l; ++i)
        if (a == arr[i]) return true;
    return false;
}

int main()
{
    const int X = 42;
    int n, nums[10], i, j;
    for (i = 0; i < 10; ++i)
    {
        scanf("%d", &n);
        nums[i] = n % X;
    }
    int count = 1;
    for (i = 1; i < 10; ++i)
        if (!inArray(nums[i], nums, i)) count++;
    printf("%d", count);
}