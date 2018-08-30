// P1917 三子棋II
// https://www.luogu.org/problemnew/show/P1917

#include <cstdio>
#include <iostream>
#include <map>
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

int play_board(string b, int step)
{
    int state = 0, i;
    char c = step & 1 ? 'O' : 'X';
    bool gameover = true;

    // printf("%d\n", step);
    // print_board(b);

    for (i = 0; i < 9; ++i)
    {
        if (b[i] == '-')
        {
            gameover = false;
            b[i] = c; // play O/X on i;
            state = check_board(b, i);
            b[i] = '-';

            if (state) return state;
        }
    }
    if (gameover) return 0;  // tie

    state = -2;
    for (i = 0; i < 9; ++i)
    {
        if (b[i] == '-')
        {
            b[i] = c; // play O/X on i;
            state = max(state, - play_board(b, step + 1));
            b[i] = '-';
        }
    }
    // printf("%d\n", step);
    // print_board(b);
    return state;
}

int main()
{
    char b[10];
    // char b[10] = "XOXO-X--O";
    // char b[10] = "-X--O--O-";
    scanf("%s", b);
    scanf("%s", &b[3]);
    scanf("%s", &b[6]);

    int step = 0;
    for (int i = 0; i < 9; ++i)
        if (b[i] != '-') step++;

    // print_board(b);

    int state = play_board(b, step + 1);

    if (step & 1)   // play_x
        state = -state;

    if (state == 0)
        cout << "Dont know.\n" << step;
    else if (state == 1)
        cout << "xiaoa will win.\n" << step;
    else
        cout << "uim will win.\n" << step;

}