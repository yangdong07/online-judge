/*
ID: yesimim1
TASK: lamps
LANG: C++

#include <cstdio>

#include <fstream>
    ofstream fout ("lamps.out");
    ifstream fin ("lamps.in");
*/

#include <cstdio>
#include <string>
#include <algorithm>

using namespace std;

FILE *fin = fopen("lamps.in", "r");
FILE *fout = fopen("lamps.out", "w");

const int N_SWITCHS = 4;
const int PERIOD = 6;    // lamps status is repeat every 6 lamp
const string base_lamp = "000000";


int switchs[N_SWITCHS] = {
    0b111111, // switch all lamp
    0b010101, // switch lamp in 'odd'
    0b101010, // switch lamp in 'even'
    0b001001  // switch lamp in '3k + 1'
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


string convert_lamp(int lamp)
{
    string s = base_lamp;
    for (int t = lamp, j = 0; j < PERIOD; t >>= 1)
        s[j++] = '0' + (t & 1);
    return s;
}


int search_lamps(string lamps[], int states[], int n_states, int on, int off)
{
    int i, j, t, k = 0, lamp;
    for (i = 0; i < n_states; ++i)
    {
        lamp = (1 << PERIOD) - 1;   // all lamps are on
        for (t = states[i], j = 0; t; t >>= 1, ++j)
            if (t & 1)
                lamp ^= switchs[j];  // switch j;
        if ((lamp & on) == on && (~lamp & off) == off)
            lamps[k++] = convert_lamp(lamp);
    }
    return k;
}


void print_lamps(string lamp, int n)
{
    int i, j;
    for (i = 0; i < n / PERIOD; ++i)
        for (j = 0; j < PERIOD; ++j)
            fputc(lamp[j], fout);
    for (j = 0; j < n % PERIOD; ++j)
        fputc(lamp[j], fout);
    fputc('\n', fout);
}

int main()
{
    int n, c, i;
    fscanf(fin, "%d %d", &n, &c);

    int lamp_on = 0, lamp_off = 0;
    // lamp_on
    for (fscanf(fin, "%d", &i); i != -1; fscanf(fin, "%d", &i))
        lamp_on |= (1 << ((i - 1) % PERIOD));
    // lamp off
    for (fscanf(fin, "%d", &i); i != -1; fscanf(fin, "%d", &i))
        lamp_off |= (1 << ((i - 1) % PERIOD));

    int states[1 << N_SWITCHS];
    int n_states = search_state(states, c, N_SWITCHS);

    // for (int i = 0; i < n_states; ++i)
    //     fprintf(fout, "%d ", states[i]);
    // fprintf(fout, "\n");

    string lamps[1 << PERIOD];
    int n_lamps = search_lamps(lamps, states, n_states, lamp_on, lamp_off);

    if (n_lamps == 0)
    {
        fprintf(fout, "IMPOSSIBLE\n");
        return 0;
    }

    sort(lamps, lamps + n_lamps);

    for (i = 0; i < n_lamps; ++i)
    {
        // fprintf(fout, "%3d: ", lamps[i]);
        print_lamps(lamps[i], n);
    }

    return 0;
}