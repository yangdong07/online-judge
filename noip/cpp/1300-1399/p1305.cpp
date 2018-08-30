// P1305 新二叉树
// https://www.luogu.org/problemnew/show/P1305

#include <cstdio>

struct node
{
    int c;
    int p;  // parent
    int l;  // left
    int r;  // right
};

void print_preorder(node a[], int x)
{
    putchar(a[x].c);
    if (a[x].l != -1)
        print_preorder(a, a[x].l);
    if (a[x].r != -1)
        print_preorder(a, a[x].r);
}

int main()
{
    const int MAX_N = 27;
    int n;
    char s[5];  // c, l, r
    node a[MAX_N];

    scanf("%d", &n);

    // init
    for (int i = 0; i < MAX_N; ++i)
        a[i].c = a[i].l = a[i].r = a[i].p = -1;

    // fill
    for (int i = 0, j; i < n; ++i)
    {
        scanf("%s", s);
        j = s[0] - 'a';
        a[j].c = s[0];
        if (s[1] != '*')
        {
            a[j].l = s[1] - 'a';
            a[a[j].l].p = j;
        }
        if (s[2] != '*')
        {
            a[j].r = s[2] - 'a';
            a[a[j].r].p = j;
        }
    }

    int i = 0;
    while (a[i].c == -1) ++i;
    while (a[i].p != -1) i = a[i].p;

    print_preorder(a, i);

    return 0;
}