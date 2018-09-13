
// P2730 魔板 Magic Squares
// https://www.luogu.org/problemnew/show/P2730

#include <cstdio>
#include <iostream>
#include <string>
#include <set>
#include <queue>
#include <algorithm>

using namespace std;

const int N = 8;
const int HN = N >> 1;       // half N
const int MAX_N = 40320 + 1; // 8! = 40320

set<string> visit;
int operations[MAX_N];
int depth;
string target = "12345678";
string operate(string &s, int op);


bool dfs(string s, int d)
{
    if (d == depth)
        return s == target;
    
    if (visit.count(s) > 0)
        return false;

    // cout << d << " " << s << endl;
    visit.insert(s);
    
    for (int i = 0; i < 3; ++i)
    {
        operations[d] = i;
        if (dfs(operate(s, i), d + 1))
            return true;
    }
    // visit.erase(s);
    return false;
}

int main()
{
    string s = "12345678";
    int i = 0;
    char c;
    while (cin >> c && !cin.eof())
        target[i++] = c;
    // cout << target << endl << endl;

    target = "41235876";
    for (depth = 0; depth < MAX_N; ++depth)
    {
        visit.clear();
        if (dfs(s, 0)) break;
    }
    cout << depth << endl;
    for (i = 0; i < depth; ++i)
        cout << (char)('A' + operations[i]);

    return 0;
}


string op_a(string s)
{
    // 12345678 -> 87654321
    reverse(s.begin(), s.end());
    return s;
}

string op_b(string &s)
{
    // 12345678 -> 41236785
    string s2 = s;
    for (int i = 1; i < N / 2; ++i)
    {
        s2[i] = s[i - 1];
        s2[N - i - 1] = s[N - i];
    }
    s2[0] = s[N / 2 - 1];
    s2[N - 1] = s[N / 2];
    return s2;
}

string op_c(string s)
{
    // 12345678 -> 17245368
    string s2 = s;
    s2[1] = s[6];
    s2[2] = s[1];
    s2[5] = s[2];
    s2[6] = s[5];
    return s2;
}

string operate(string &s, int op)
{
    switch (op)
    {
        case 0: return op_a(s);
        case 1: return op_b(s);
        case 2: return op_c(s);
    }
    return s;
}