
// P2724 联系 Contact
// https://www.luogu.org/problemnew/show/P2724

#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>

using namespace std;

const int MAX_L = 12 + 1;
const int MAX_N = 1 << 12;
const int MAX_S = 200000 + 1;

char s[MAX_S];

struct Frequency
{
    int l, n, f;
    Frequency() {}
    Frequency(int l, int n, int f) : l(l), n(n), f(f) {}

    bool operator<(const Frequency &rhs) const
    {
        if (f != rhs.f)
            return f < rhs.f;
        if (l != rhs.l)
            return l > rhs.l;
        return n > rhs.n;
    }
};

void print_bin(int n, int l)
{
    if (l == 0) return;
    print_bin(n >> 1, l - 1);
    putchar(n & 1 ? '1' : '0');
}

int main()
{
    int a, b, n, i, j;
    int count[MAX_L][MAX_N] = {0};
    scanf("%d %d %d", &a, &b, &n);

    int len = 0;
    for (char c = getchar(); c != EOF; c = getchar())
        if (c == '0' || c == '1') s[len++] = c;

    int num, mask;
    for (i = a; i <= b; ++i)
    {
        mask = (1 << i) - 1;
        for (num = j = 0; j < i - 1; ++j)
            num = (num << 1) + (s[j] - '0');
        for (; j < len; ++j)
        {
            num = (num << 1 & mask) + (s[j] - '0');
            count[i][num]++; 
        }
    }
    priority_queue<Frequency> pq;

    for (i = a; i <= b; ++i)
        for (j = 0; j < (1 << i); ++j)
            if (count[i][j])
                pq.push(Frequency(i, j, count[i][j]));

    int key = 0;  // group by key
    Frequency f;
    for (i = 0; !pq.empty(); pq.pop())
    {
        f = pq.top();
        if (f.f != key)
        {
            if (i >= n) break;  // terminate
            if (i > 0) putchar('\n');
            key = f.f;
            ++i, j = 0;
            printf("%d", key);  // group start
        }
        putchar((j++ % 6 == 0) ? '\n' : ' ');
        print_bin(f.n, f.l);
    }
    return 0;
}