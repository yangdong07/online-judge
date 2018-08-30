// P1160 队列安排
// https://www.luogu.org/problemnew/show/P1160


#include <cstdio>

struct student
{
    int id;
    student *left;
    student *right;
    bool removed;
};

int main()
{
    const int MAX_N = 100001;
    student s[MAX_N];  // all ~~stupid~~ students

    int n, m, i;
    scanf("%d", &n);

    // fisrt stupid
    s[1].id = 1;
    s[1].left = s[1].right = NULL;
    s[1].removed = false;

    // insert
    int k, lr;
    student *leftmost = &s[1];
    for (i = 2; i <= n; ++i)
    {
        scanf("%d %d", &k, &lr);
        // insert s[i] to s[k]'s left or right
        // printf("insert %d to %d' %s\n", i, k, lr ? "right" : "left");
        s[i].id = i;
        s[i].removed = false;
        if (lr == 0)  // left
        {
            s[i].left = s[k].left;
            s[i].right = &s[k];
            if (s[k].left != NULL)
                s[k].left->right = &s[i];
            s[k].left = &s[i];

            if (s[i].left == NULL)
                leftmost = &s[i];
        }
        else
        {
            s[i].right = s[k].right;
            s[i].left = &s[k];
            if (s[k].right != NULL)
                s[k].right->left = &s[i];
            s[k].right = &s[i];
        }
    }

    scanf("%d", &m);

    for (i = 0; i < m; ++i)
    {
        scanf("%d", &k);
        s[k].removed = true;
    }

    student *it = leftmost;
    printf("%d", it->id);
    for (it = it->right; it != NULL; it = it->right)
        if (!it->removed) printf(" %d", it->id);
    printf("\n");

    return 0;
}