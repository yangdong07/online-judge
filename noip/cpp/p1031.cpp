// P1031 均分纸牌
// https://www.luogu.org/problemnew/show/P1031

#include <iostream>

using namespace std;

#define MAX_N 100

int main()
{
    int n;
    cin >> n;

    int i, avg = 0;
    int a[MAX_N];
    for (i = 0; i < n; ++i)
    {
        cin >> a[i];
        avg += a[i];
    }
    avg /= n;
    
    int r = 0, count = 0;
    for (i = 0; i < n; ++i)
    {
        r += a[i] - avg;
        if (r) count++;
    }
    cout << count;
}