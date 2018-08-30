// P1059 明明的随机数
// https://www.luogu.org/problemnew/show/P1059

#include <iostream>
#include <algorithm>

using namespace std;

#define MAX_N 100

int main() {
    int n, i;
    int random[MAX_N];
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        scanf("%d", &random[i]);
    }
    sort(random, random + n);
    // de-duplicate
    int ii = 0;  // following index
    for (i = 1; i < n; i++) {
        if (random[i] != random[ii]) {
            random[++ii] = random[i];
        }
    }
    printf("%d\n%d", ++ii, random[0]);
    for (i = 1; i < ii; i++) {
        printf(" %d", random[i]);
    }
}