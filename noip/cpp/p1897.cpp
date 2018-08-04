// P1897 电梯里的爱情
// https://www.luogu.org/problemnew/show/P1897


#include <iostream>
#include <set>
#include <algorithm>

using namespace std;

int main()
{
    set<int> floors;
    int n, i, flr, max_flr = 0;
    cin >> n;
    for (i = 0; i < n; ++i)
    {
        cin >> flr;
        floors.insert(flr);
        max_flr = max(flr, max_flr);
    }

    int answer = max_flr * 10 + floors.size() * 5 + n;

    cout << answer;
}