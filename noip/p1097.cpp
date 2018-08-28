// P1097 统计数字
// https://www.luogu.org/problemnew/show/P1097

#include <cstdio>
#include <map>
#include <algorithm>

#define MAX_N 10001

int read_num()
{
    char c;
    int num = 0;
    for (c = getchar(); c < '0' || c > '9'; c = getchar());

    for (; c >= '0' && c <= '9'; c = getchar())
        num = num * 10 + c - '0';
    return num;
}

int nums[MAX_N], count[MAX_N], k[MAX_N];
bool cmp(int i, int j) { return nums[i] < nums[j]; }

int main()
{
    int n, i, num;
    n = read_num();
    std::map<int, int> counter;

    for (i = 0; i < n; ++i)
    {
        num = read_num();
        if (counter.count(num) == 0)
            counter[num] = 1;
        else
            ++counter[num];
    }

    std::map<int, int>::iterator it;
    for (i = 0, it = counter.begin(); it != counter.end(); ++it, ++i)
    {
        nums[i] = it->first;
        count[i] = it->second;
        k[i] = i;
    }

    n = i;
    std::sort(k, k + n, cmp);

    for (i = 0; i < n; ++i)
        printf("%d %d\n", nums[k[i]], count[k[i]]);

    return 0;
}