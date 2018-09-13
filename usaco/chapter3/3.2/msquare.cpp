/*
ID: yesimim1
TASK: msquare
LANG: C++

#include <cstdio>
FILE *fin = fopen ("msquare.in", "r");
FILE *fout = fopen ("msquare.out", "w");

void _fputc(char c) { fputc(c, fout); }

#include <fstream>
    ofstream fout ("msquare.out");
    ifstream fin ("msquare.in");
*/

#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>

using namespace std;

FILE *fin = fopen ("msquare.in", "r");
FILE *fout = fopen ("msquare.out", "w");

void _fputc(char c) { fputc(c, fout); }

const int N = 8;
const int MAX_N = 40320 + 1;  // 8!

int target;
int depth[MAX_N] = {0};
int pi[MAX_N]; // parent index;
int operation[MAX_N];

int elements[] = {1, 2, 3, 4, 5, 6, 7, 8};

int permutation_k(int a[])
{
    int i, j, n, k = 0;
    for (i = 0; i < N; ++i)
    {
        for (n = 0, j = i + 1; j < N; ++j)
            if (a[j] < a[i]) ++n;
        k = k * (N - i) + n;
    }
    return k;
}

void kth_permutation(int k, int a[])
{
    int i, j, n;
    for (i = N - 1; i >= 0; --i)
    {
        a[i] = k % (N - i);
        k /= (N - i);
    }
    bool used[N] = {false};
    for (i = 0; i < N; ++i)
    {
        for (n = -1, j = 0; j < N; ++j)
        {
            if (!used[j]) ++n;
            if (n == a[i])
            {
                a[i] = elements[j], used[j] = true;
                break;
            }
        }
    }
    // for (i = 0; i < N; ++i)
    //     fprintf(fout, "%d ", a[i]);
    // fprintf(fout, "\n");
}

void op_a(int a[N])
{
    // 12345678 -> 87654321
    reverse(a, a + N);
}

void op_b(int a[N])
{
    // 12345678 -> 41236785
    for (int i = N / 2 - 1; i > 0; --i) 
        swap(a[i], a[i - 1]);
    for (int i = N / 2; i < N - 1; ++i)
        swap(a[i], a[i + 1]);
}

void op_c(int a[N])
{
    // 12345678 -> 17245368
    // 1 -> 2 -> 5 -> 6
    swap(a[5], a[6]);
    swap(a[2], a[5]);
    swap(a[1], a[2]);
}

int operate(int k, int i)
{
    int a[N];
    kth_permutation(k, a);
    // for (int j = 0; j < N; ++j)
    //     fprintf(fout, "%d ", a[j]);
    // fprintf(fout, "\n");
    if (i == 0)
        op_a(a);
    else if (i == 1)
        op_b(a);
    else if (i == 2)
        op_c(a);

    // for (int j = 0; j < N; ++j)
    //     fprintf(fout, "%d ", a[j]);
    // fprintf(fout, "\n");
    return permutation_k(a);
}

void bfs(int start)
{
    queue<int> q;
    q.push(start);
    depth[start] = 1;
    while (!q.empty())
    {
        int k = q.front();
        q.pop();
        if (k == target)
            return;
        for (int i = 0; i < 3; ++i)
        {
            int next = operate(k, i);
            if (!depth[next])
            {
                depth[next] = depth[k] + 1;
                pi[next] = k;
                operation[next] = i;
                q.push(next);
            }
        }
    }
}

void print_operation(int i)
{
    if (i == 0) return;
    print_operation(pi[i]);
    _fputc('A' + operation[i]);
    // _fputc('\n');
    // int a[N];
    // kth_permutation(i, a);
    // for (int j = 0; j < N; ++j)
    //     fprintf(fout, "%d ", a[j]);
    // fprintf(fout, "\n");
}


int main()
{
    int a[N];
    for (int i = 0; i < N; ++i)
        fscanf(fin, "%d", &a[i]);
    
    target = permutation_k(a);

    bfs(0);
    fprintf(fout, "%d\n", depth[target] - 1);
    print_operation(target);
    // fprintf(fout, "%d\n", target);
    fprintf(fout, "\n");

    // kth_permutation(target, a);
    // for (int i = 0; i < 10; ++i)
    // {
    //     kth_permutation(i, a);
    //     fprintf(fout, "%d\n", permutation_k(a));
    // }
    return 0;
}