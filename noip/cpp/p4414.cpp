// P4414 [COCI2006-2007#2] ABC
// https://www.luogu.org/problemnew/show/P4414

#include <cstdio>

void swap(int *a, int *b)
{
    int t = *b;
    *b = *a;
    *a = t;
}

int main()
{
    int a[3];
    char s[5];
    scanf("%d %d %d", &a[0], &a[1], &a[2]);

    // sort
    if (a[0] > a[1]) swap(&a[0], &a[1]);
    if (a[1] > a[2]) swap(&a[1], &a[2]);
    if (a[0] > a[1]) swap(&a[0], &a[1]);

    scanf("%s", s);

    printf("%d %d %d", a[s[0] - 'A'], a[s[1] - 'A'], a[s[2] - 'A']);

}