// P1481 魔族密码
// https://www.luogu.org/problemnew/show/P1481

#include <iostream>
#include <string>

using namespace std;

#define MAX_N 2001

bool comparable(string a, string b)
{
    return b.find(a) == 0;
}

void find_replace(string a[], int n, string s)
{
    int l = 0, r = n, m;
    while (l < r)
    {
        m = (l + r) / 2;
        if (comparable(a[m], s)) l = m + 1;
        else r = m;
    }
    a[l] = s;
}

int main()
{
    int n, i, j;
    string s[MAX_N], t[MAX_N];

    cin >> n;
    for (i = 0; i < n; ++i)
        cin >> s[i];
    

    // find max longest chain
    t[0] = s[0];
    for (i = 1, j = 0; i < n; ++i)
    {
        if (comparable(t[j], s[i]))
            t[++j] = s[i];
        else
            find_replace(t, j, s[i]);
    }
    cout << j + 1 << endl;
    return 0;
}