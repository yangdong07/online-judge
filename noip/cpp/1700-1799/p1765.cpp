// P1765 手机_NOI导刊2010普及（10）
// https://www.luogu.org/problemnew/show/P1765

#include <iostream>
#include <string>

using namespace std;

int clicks[256] = { 0 };

void init_clicks()
{
    const string keyboard[12] = {
        "",     "abc",  "def", 
        "ghi",  "jkl",  "mno", 
        "pqrs", "tuv",  "wxyz", 
        "*",    " ",    "#"};

    for (int i = 0; i < 12; ++i)
        for (int j = 0; j < keyboard[i].length(); ++j)
            clicks[keyboard[i][j]] = j + 1;
}

int main()
{
    init_clicks();

    string s;
    getline(cin, s);

    int count = 0;

    for (int i = 0; i < s.length(); ++i)
        count += clicks[s[i]];

    cout << count;

}