// P1803 凌乱的yyy / 线段覆盖
// https://www.luogu.org/problemnew/show/P1803

#include <iostream>
#include <algorithm>

#define MAX_N 1000001

using namespace std;

struct Activity
{
    int start;
    int finish;
};

bool cmp(Activity &a, Activity &b)
{
    return a.finish < b.finish;
}

int main()
{
    int n, i;
    Activity a[MAX_N];

    cin >> n;
    for (i = 0; i < n; ++i)
        cin >> a[i].start >> a[i].finish;

    sort(a, a + n, cmp);

    int lf = 0; // last finish
    int count = 0;

    for (i = 0; i < n; ++i)
    {
        if (a[i].start >= lf)
        {
            count++;
            lf = a[i].finish;
        }
    }

    cout << count << endl;
    return 0;
}