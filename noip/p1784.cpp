// P1784 数独
// https://www.luogu.org/problemnew/show/P1784

#include <cstdio>
#include <string>
#include <algorithm>
#include <set>

using namespace std;
 
#define SQRTN 3
#define N 9
#define NN 81   // 9 * 9
#define UNASSIGNED 0

const string DIGITS = "123456789";

void display(string &g);    // display grid
void display(string v[NN]); // values of each position
void init();                // init units and peers

// assign d to v[k], try eliminate other digits from v[k];
bool assign(string v[NN], int k, char d); 
// eliminate d from v[k], propagate if possible
bool eliminate(string v[NN], int k, char d);  
// search result from all possible
bool search(string v[NN]);


set<int> units[3][NN]; // row, col, box
set<int> peers[NN];


void print_grid(string v[NN])
{
    int i, j;
    for (i = 0; i < N; ++i)
    {
        for (j = 0; j < N; ++j)
        {
            if (j > 0) putchar(' ');
            putchar(v[i * N + j][0]);
        }
        putchar('\n');
    }
}

void display(string v[NN])
{
    int i, j;
    int width = 0;
    for (i = 0; i < NN; ++i)
        width = max(width, int(v[i].size()));
    width++;

    for (i = 0; i < N; ++i)
    {
        for (j = 0; j < N; ++j)
        {
            printf("%-*s", width, v[i * N + j].c_str());
            if (j == 2 || j == 5) printf("| ");
        }
        if (i == 2 || i == 5)
        {
            putchar('\n');
            for (j = 0; j < width * SQRTN; ++j) putchar('-');
            putchar('+');
            for (j = 0; j <= width * SQRTN; ++j) putchar('-');
            putchar('+');
            for (j = 0; j < width * SQRTN; ++j) putchar('-');
        }
        putchar('\n');
    }
    // putchar('\n');
}

void display(string &g)
{
    string v[NN];
    for (int i = 0; i < NN; ++i)
        v[i] = g[i] == '0' ? "." : g.substr(i, 1);
    display(v);
}

void init()
{
    int i, j, k, r, c;
    // init units and peers
    for (k = 0; k < NN; ++k)
    {
        // rows
        r = (k / N) * N;  // row start
        for (i = r; i < r + N; ++i) 
        {
            units[0][k].insert(i);
            peers[k].insert(i);
        }
        // columns
        c = k % N;
        for (i = 0; i < N; ++i)
        {
            units[1][k].insert(i * N + c);
            peers[k].insert(i * N + c);
        }
        // boxes
        r = (k / N / SQRTN) * SQRTN;
        c = (k % N / SQRTN) * SQRTN;
        for (i = r; i < r + SQRTN; ++i)
            for (j = c; j < c + SQRTN; ++j)
            {
                units[2][k].insert(i * N + j);
                peers[k].insert(i * N + j);
            }
    }
    // each peer erase self
    for (k = 0; k < NN; ++k)
        peers[k].erase(k);

    // // test print
    // for (k = 0; k < NN; ++k)
    // {
    //     printf("%d's units: ", k);
    //     for (int z = 0; z < 3; ++z)
    //         for (set<int>::iterator it = units[z][k].begin(); it != units[z][k].end(); ++it)
    //             printf("%d ", *it);
    //     printf("\n");
    //     printf("%d's peers: ", k);
    //     for (set<int>::iterator it = peers[k].begin(); it != peers[k].end(); ++it)
    //         printf("%d ", *it);
    //     printf("\n");
    // }
}

bool assign(string v[NN], int k, char d)
{
    // assign d to v[k], eliminate all the other values from v[k]
    // and propagate if possible
    // return true if no contradiction is detected.
    bool flag = true; // no contradiction flag
    string t = v[k];
    size_t i = t.find(d);
    if (i != string::npos)
        t.erase(i, 1);

    // if (t.size() > 0) printf("assign %c to v[%d][%d]\n", d, k / N, k % N);
    for (i = 0; i < t.size(); ++i)
        flag = eliminate(v, k, t[i]) && flag;

    return flag;
}

bool eliminate(string v[NN], int k, char d)
{
    // eliminate d from v[k];
    // propagate when values or places <= 2.
    // return true if no contracdiction detected, otherwise false
    size_t i = v[k].find(d);
    if (i == string::npos) return true;

    // printf("eliminate %c from v[%d][%d]\n", d, k / N, k % N);
    v[k].erase(i, 1);

    bool flag = true;
    set<int>::iterator it;
    // (1) if v[k] is reduced to 1 value d2, eliminate d2 from peers;
    if (v[k].size() == 0)
        return false;   // !!!contradiction: no possible value here
    else if (v[k].size() == 1)
    {
        char d2 = v[k][0];
        for (it = peers[k].begin(); it != peers[k].end(); ++it)
            flag = eliminate(v, *it, d2) && flag;
        if (!flag) return false;
    }

    // (2) if a unit u is reduced to only one place for a value d, then put it there
    int j, dplaces[N];
    for (int u = 0; u < 3; ++u)
    {
        j = 0;
        for (it = units[u][k].begin(); it != units[u][k].end(); ++it)
        {
            // printf("%d %s\n", *it, v[*it].c_str());
            if (v[*it].find(d) != string::npos)
                dplaces[j++] = *it;
        }
        // printf("%d\n", j);
        if (j == 0)
            return false;   // contradiction: no place for this value;
        else if (j == 1)
            if (!assign(v, dplaces[0], d))
                return false;
    }
    return true;
}

bool parse_grid(string &g, string v[NN])
{
    for (int i = 0; i < NN; ++i)
        v[i] = DIGITS; // 123456789
    for (int i = 0; i < NN; ++i)
    {
        if ((DIGITS.find(g[i]) != string::npos) && !assign(v, i, g[i]))
            return false;
    }
    return true;
}


// int search_count = 0;
bool search(string v[NN])
{
    // search_count++;
    int i = 0;
    while (i < NN && v[i++].size() == 1);
    if (i == NN)
    {
        // found solution
        // display(v);
        print_grid(v);
        return true;
    }

    // find the shortest/most possible
    int min_l = N, k;
    for (i = 0; i < NN; ++i)
        if (v[i].size() > 1 && v[i].size() < min_l)
        {
            min_l = v[i].size();
            k = i;
        }
    // try assign every possible
    string vc[NN]; // copy of v[NN];
    for (i = 0; i < v[k].size(); ++i)
    {
        copy(v, v + NN, vc);
        if (!assign(vc, k, v[k][i])) continue;
        if (search(vc)) return true;
    }
    return false;
}


int main()
{
    init();

    int t;
    string grid = "8..........36......7..9.2...5...7.......457.....1...3...1....68..85...1..9....4..";
    string v[NN];

    for (int i = 0; i < NN; ++i)
    {
        scanf("%d", &t);
        grid[i] = '0' + t;
    }

    // string grid = "003020600900305001001806400008102900700000008006708200002609500800203009005010300";
    // string grid = "4.....8.5.3..........7......2.....6.....8.4......1.......6.3.7.5..2.....1.4......";
    // string grid = "7..9....11....59.....2...8...5.2...3......648413........7..2.9.2.1.6.8.4.8.5.4.12";
    // string grid = "8..........36......7..9.2...5...7.......457.....1...3...1....68..85...1..9....4..";
    // display(grid);
    parse_grid(grid, v);

    search(v);
    
    // printf("search count: %d\n", search_count);
    // display(v);
    // string s = "123";
    // printf("%s\n", s.c_str());
    // // if (s.find('4') != string::npos)
    //     s.erase(s.find('4'), 1);
    // printf("%s\n", s.c_str());
    return 0;
}