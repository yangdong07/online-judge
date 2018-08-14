// P1032 字串变换
// https://www.luogu.org/problemnew/show/P1032

#include <iostream>
#include <queue>
#include <string>
#include <map>

using namespace std;

map<string, int> stc;  // string transfer counter

const int MAX_N = 7;
string a, b;
string A[MAX_N], B[MAX_N];
int n;

int bfs()
{
    queue<string> q;
    int d;
    string s, t;
    size_t pos;

    q.push(a);
    stc[a] = 0;
    while (!q.empty())
    {
        s = q.front();
        d = stc[s];
        q.pop();

        if (d == 10) break;

        for (int i = 0; i < n; ++i)
        {
            pos = s.find(A[i]);
            while (pos != string::npos)
            {
                t = s;
                t.replace(pos, A[i].length(), B[i]);
                if (stc.count(t) == 0)
                {
                    if (t == b) return (d + 1);
                    // cout << s << " -> " << t << endl;
                    stc[t] = d + 1;
                    q.push(t);
                }
                pos = s.find(A[i], pos + 1);
            }
        }
    }
    return -1;
}

int main()
{
    cin >> a >> b;
    n = 0;
    while (cin >> A[n] >> B[n]) ++n;

    int ans = bfs();

    if (ans == -1)
        cout << "NO ANSWER!" << endl;
    else
        cout << ans << endl;

    return 0;
}