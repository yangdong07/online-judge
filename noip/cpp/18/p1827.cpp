
// P1827 美国血统 American Heritage
// https://www.luogu.org/problemnew/show/P1827

#include <cstdio>
#include <cstring>


int search(char a[], char x, int n)
{
    for (int i = 0; i < n; ++i)
        if (a[i] == x)
            return i;
    return -1;
}

void print_postorder(char in[], char pre[], int n)
{
    int root = search(in, pre[0], n);
    if (root != 0)
        print_postorder(in, pre + 1, root);
    if (root != n - 1)
        print_postorder(in + root + 1, pre + root + 1, n - root - 1);

    putchar(in[root]);
}

int main()
{
    const int MAX_N = 30;
    char inorder[MAX_N];
    char preorder[MAX_N];

    scanf("%s %s", inorder, preorder);

    print_postorder(inorder, preorder, strlen(inorder));

    return 0;
}