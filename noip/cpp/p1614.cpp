// P1614 爱与愁的心痛
// https://www.luogu.org/problemnew/show/P1614

#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
    int n, m, i;
    cin >> n >> m;

    int values[3001] = { 0 };

    int v, sum = 0;

    for (i = 0; i < m; ++i)
    {
        cin >> v;
        values[i] = v;
        sum += v;
    }
    int min_sum = sum;
    for ( ; i < n; ++i)
    {
        cin >> v;
        sum = sum - values[i % m] + v;
        min_sum = min(min_sum, sum);
        values[i % m] = v;
    }
    cout << min_sum;

}