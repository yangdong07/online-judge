
// P2256 一中校运会之百米跑
// https://www.luogu.org/problemnew/show/P2256


#include <iostream>
#include <string>
#include <map>

using namespace std;

const int MAX_N = 20001;

int s[MAX_N] = {0};

int find(int x)
{
    if (s[x] == x)
        return x;
    return s[x] = find(s[x]);
}

void unite(int x, int y)
{
    s[find(x)] = find(y);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n, m, i, k;
    cin >> n >> m;

    string a, b;
    map<string, int> names;

    for (i = 1; i <= n; ++i)
    {
        cin >> a;
        names[a] = i;
        s[i] = i;
    }

    for (i = 0; i < m; ++i)
    {
        cin >> a >> b;
        unite(names[a], names[b]);
    }

    cin >> k;

    for (i = 0; i < k; ++i)
    {
        cin >> a >> b;
        cout << (find(names[a]) == find(names[b]) ? "Yes." : "No.") << endl;
    }
    return 0;
}