// P1838 三子棋I
// https://www.luogu.org/problemnew/show/P1838


#include <cstdio>
#include <iostream>
#include <string>

using namespace std;

void print_board(string b)
{
    for (int i = 0; i < 9; ++i)
    {
        putchar(b[i]);
        if (i % 3 == 2) putchar('\n');
    }
}

bool check_step(string b, int k)
{
    char c = b[k];
    int i = (k / 3) * 3;

    // row
    if (b[i] == c && b[i + 1] == c && b[i + 2] == c) return true;

    // column
    i = k % 3;
    if (b[i] == c && b[i + 3] == c && b[i + 6] == c) return true;

    // slash
    return (k % 2 == 0 && b[4] == c && ((b[0] == c && b[8] == c) || (b[2] == c && b[6] == c)));
}


int main()
{
    string s, b = "---------";

    cin >> s;

    for (int i = 0; i < s.length(); ++i)
    {
        b[s[i] - '1'] = i & 1 ? 'X' : 'O';
    }

    bool ow = false, xw = false;
    for (int i = 0; i < s.length(); ++i)
    {
        if (b[i] == 'O')
            ow = ow || check_step(b, i);
        else if (b[i] == 'X')
            xw = xw || check_step(b, i);
    }
    if (!(ow ^ xw))
        cout << "drew.";
    else if (ow)
        cout << "xiaoa wins.";
    else
        cout << "uim wins.";
}