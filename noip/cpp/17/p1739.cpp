// P1739 表达式括号匹配
// https://www.luogu.org/problemnew/show/P1739

#include <iostream>

using namespace std;

#define MAX_N 22

int main()
{
    string s;
    cin >> s;

    int stack[MAX_N], j = 0;

    for (int i = 0; i < s.length(); ++i)
    {
        if (s[i] == '(')
            stack[j++] = '(';
        else if (s[i] == ')')
        {
            if (j == 0)
            {
                cout << "NO";
                return 0;
            }
            else
                j--;
        }
    }
    cout << (j == 0 ? "YES" : "NO");
}