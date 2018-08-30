// P1914 小书童——密码
// https://www.luogu.org/problemnew/show/P1914

#include <iostream>

using namespace std;

int main()
{
    int n;
    string s;

    cin >> n >> s;

    for (int i = 0; i < s.length(); ++i)
    {
        s[i] = (s[i] - 'a' + n) % 26 + 'a';
    }

    cout << s;
}