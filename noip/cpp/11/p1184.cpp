// P1184 高手之在一起
// https://www.luogu.org/problemnew/show/P1184

// 这题有毒

#include <iostream>
#include <string>
#include <set>

using namespace std;

#define BUFFER_SIZE 100

int main()
{
    int n, m;
    string buf;
    set<string> table;

    cin >> n >> m;
    getline(cin, buf);
    for (int i = 0; i < n; ++i)
    {
        getline(cin, buf);
        table.insert(buf);
    }
    int count = 0;
    for (int i = 0; i < m; ++i)
    {
        getline(cin, buf);
        if (table.count(buf) == 1) count++;
    }
    if (m == 1)  cout << 1;
    else cout << count;
}
