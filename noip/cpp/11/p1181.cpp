// P1181 数列分段Section I
// https://www.luogu.org/problemnew/show/P1181

#include <cstdio>

int main()
{
    int n, m, a;
    scanf("%d %d", &n, &m);
    int count = 1, section = 0;
    for (int i = 0; i < n; ++i) {
        scanf("%d", &a);
        if (section + a > m) {
            count++;
            section = a;
        } else {
            section += a;
        }
    }
    printf("%d", count);
}