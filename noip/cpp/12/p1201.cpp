
// P1201 [USACO1.1]贪婪的送礼者Greedy Gift Givers
// https://www.luogu.org/problemnew/show/P1201

#include <iostream>
#include <string>
#include <map>

using namespace std;

int main()
{
    const int MAX_N = 12;
    map<string, int> balance;
    int n, i;
    string name;
    string names[MAX_N];

    cin >> n;
    for (i = 0; i < n; ++i)
    {
        cin >> name;
        balance[name] = 0;
        names[i] = name;
    }

    int given, m, j, average;
    for (i = 0; i < n; ++i)
    {
        cin >> name >> given >> m;
        average = m > 0 ? given / m : 0;
        balance[name] -= average * m;

        for (j = 0; j < m; ++j)
        {
            cin >> name;
            balance[name] += average;
        }
    }

    for (i = 0; i < n; ++i)
        cout << names[i] << " " << balance[names[i]] << endl;

    return 0;
}