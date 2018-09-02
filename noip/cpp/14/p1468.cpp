
// P1468 派对灯 Party Lamps
// https://www.luogu.org/problemnew/show/P1468

#include <cstdio>

const int N_SWITCHS = 4;
const int PERIOD = 6;    // lamps status is repeat every 6 lamp


int switchs[N_SWITCHS] = {  // from left to right, 1->6
    0b111111, // switch all lamp
    0b101010, // switch lamp in 'odd'
    0b010101, // switch lamp in 'even'
    0b100100  // switch lamp in '3k + 1'
};


int search_state(int states[], int c, int n_switchs)
{
    int i, j, t, k = 0;
    for (i = 0; i < (1 << n_switchs); ++i)
    {
        for (t = i, j = 0; t; t >>= 1)
            j += (t & 1);   // j is the number of bit 1s;
        if ((j & 1) == (c & 1) && j <= c)
            states[k++] = i;
    }
    return k;
}


void search_lamps(int lamps[], int states[], int n_states)
{
    int i, j, t, lamp;
    for (i = 0; i < n_states; ++i)
    {
        lamp = (1 << PERIOD) - 1;   // all lamps are on
        for (t = states[i], j = 0; t; t >>= 1, ++j)
            if (t & 1)
                lamp ^= switchs[j];  // switch j;
        lamps[lamp] = 1;
    }
}


void print_lamps(int lamp, int n)
{
    int on;
    for (int i = 0; i < n; ++i)
    {
        on = lamp & (1 << (PERIOD - 1 - i % PERIOD));
        printf(on ? "1" : "0");
    }
    printf("\n");
}

int main()
{
    int n, c, i;
    scanf("%d %d", &n, &c);

    int on = 0, off = 0;
    // lamp_on
    for (scanf("%d", &i); i != -1; scanf("%d", &i))
        on |= (1 << (PERIOD - 1 - (i - 1) % PERIOD));
    // lamp off
    for (scanf("%d", &i); i != -1; scanf("%d", &i))
        off |= (1 << (PERIOD - 1 - (i - 1) % PERIOD));

    int states[1 << N_SWITCHS];
    int n_states = search_state(states, c, N_SWITCHS);

    // for (int i = 0; i < n_states; ++i)
    //     printf("%d ", states[i]);
    // printf("\n");

    int lamps[1 << PERIOD] = {0};
    search_lamps(lamps, states, n_states);

    bool impossible = true;
    for (i = 0; i < (1 << PERIOD); ++i)
        if (lamps[i] == 1 && (i & on) == on && (~i & off) == off)
        {
            impossible = false;
            print_lamps(i, n);
        }

    if (impossible)
        printf("IMPOSSIBLE\n");

    return 0;
}