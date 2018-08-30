// P1320 压缩技术（续集版）
// https://www.luogu.org/problemnew/show/P1320

#include <cstdio>
#include <cstring>

#define MAX_N 200
#define MAX_NN 40000

int main()
{
    char s[MAX_N];  // use to buffer rows of matrix
    char c = '0'; // use to check the '0' or '1'

    int n;
    int i = 0, j; // row/column index of matrix
    int count[MAX_NN];
    int k = 0;    // index of count
    int cc = 0;   // counter of continous 0s/1s

    do {
        scanf("%s", s);
        n = strlen(s);
        for (j = 0; j < n; ++j) {
            if (s[j] != c) {
                count[k++] = cc;
                cc = 0;
                c = (c - '0') ^ 1 + '0';
            }
            cc += 1;
        }
        i++;
    } while (i < n);

    count[k++] = cc;

    printf("%d", n);
    for (i = 0; i < k; ++i)
        printf(" %d", count[i]);

}