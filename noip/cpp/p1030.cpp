// P1030 求先序排列
// https://www.luogu.org/problemnew/show/P1030

#include <cstdio>
#include <cstring>


int search(char a[], char x, int n)
{
    for (int i = 0; i < n; ++i)
        if (a[i] == x)
            return i;
    return -1;
}

void print_preorder(char in[], char post[], int n)
{
    int root = search(in, post[n - 1], n);
    putchar(in[root]);
    if (root != 0)
        print_preorder(in, post, root);
    if (root != n - 1)
        print_preorder(in + root + 1, post + root, n - root - 1);
}

int main()
{
    const int MAX_N = 20;
    char inorder[MAX_N];
    char postorder[MAX_N];

    scanf("%s %s", inorder, postorder);

    print_preorder(inorder, postorder, strlen(inorder));

    return 0;
}