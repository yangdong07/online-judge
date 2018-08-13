// P1040 加分二叉树
// https://www.luogu.org/problemnew/show/P1040

#include <iostream>

using namespace std;

typedef long long INT64;

const int MAX_N = 40;

int n;
int inorder[MAX_N];
int root[MAX_N][MAX_N]; // record root
INT64 s[MAX_N][MAX_N] = { 0 }; // score;

INT64 search(int l, int r)
{
    if (l > r)
        return 1; // 空子树
    else if (l == r)
        return inorder[l]; // 叶子节点分数即为本身
    else if (s[l][r])
        return s[l][r]; // 返回记忆的值

    INT64 score;

    for (int i = l; i <= r; ++i)
    {
        score = search(l, i - 1) * search(i + 1, r) + inorder[i];
        if (score > s[l][r])
        {
            s[l][r] = score;
            root[l][r] = i;
        }
    }
    return s[l][r];
}

void print_preorder(int l, int r)
{
    if (l > r) return;
    int i = root[l][r];
    cout << i << " ";
    print_preorder(l, i - 1);
    print_preorder(i + 1, r);
}

int main()
{
    cin >> n;

    for (int i = 1; i <= n; ++i)
    {
        cin >> inorder[i];
        root[i][i] = i;
    }

    cout << search(1, n) << endl;
    print_preorder(1, n);
    return 0;
}