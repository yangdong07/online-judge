// P2415 集合求和
// https://www.luogu.org/problemnew/show/P2415

#include <cstdio>

using namespace std;

#define MAX_N 30

int main()
{
    int nums[MAX_N], element;
    int n = 0, i;
    long long sum = 0;
    while (scanf("%d", &element) != EOF)
    {
        sum += element;
        n++;
    }
    printf("%lld", sum << (n - 1));
    
}