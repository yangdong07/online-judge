// P1917 三子棋II
// https://www.luogu.org/problemnew/show/P1917

#include <cstdio>
#include <iostream>
#include <map>
#include <string>

using namespace std;

enum STATE {UNKNOWN, OWIN, XWIN, TIE};

map<string, STATE> state;

void print_board(string b)
{
    for (int i = 0; i < 9; ++i)
    {
        putchar(b[i]);
        if (i % 3 == 2) putchar('\n');
    }
}

bool check_board(string b, int k)
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

STATE play_board(string b, int step)
{
    if (step == 9)
    {
        for (i = 0; i < 9; ++i)
            if (b[i] == '-')
                break;
        b[i] = 'O';
        state[b] = check_board(b, i) ? OWIN : TIE;
        return state[b];
    }

    if (state.count(b) == 1)
        return state[b];

    char c = step & 1 ? 'O' : 'X';

    for (i = 0; i < 9; ++i)
    {
        if (b[i] == '-')
        {
            b[i] = c;
            if (check_board(b, i))
            {
                if (c == 'O')
                    state[b] = OWIN;
                else
                    state[b] = XWIN;
            }
            b[i] = '-';
            return state[b];
    }
}


int main()
{
    char b[10];
    scanf("%s", b);
    scanf("%s", &b[3]);
    scanf("%s", &b[6]);

    print_board(b);

    state[b] = UNKNOWN;
    printf("%d", state[b]);

}