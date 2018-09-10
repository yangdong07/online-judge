
// P3378 【模板】堆
// https://www.luogu.org/problemnew/show/P3378

#include <cstdio>
#include <queue>

using namespace std;

void read_num(int &num)
{
    char c;
    for (c = getchar(); c < '0' || c > '9'; c = getchar());

    for (num = 0; c >= '0' && c <= '9'; c = getchar())
        num = num * 10 + c - '0';
}

int main()
{
    int n, i, op, x;
    read_num(n);
    priority_queue<int> pq;

    for (i = 0; i < n; ++i)
    {
        read_num(op);
        if (op == 1)
        {
            read_num(x);
            pq.push(-x);
        }
        else if (op == 2)
            printf("%d\n", -(pq.top()));
        else
            pq.pop();
    }

    return 0;
}