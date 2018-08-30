// P1047 校门外的树
// https://www.luogu.org/problemnew/show/P1047

#include <cstdio>
#include <array>
#include <algorithm>

using namespace std;

#define MAX_M 101

int main()
{
    int L, M;
    array<array<int, 2>, MAX_M> range;
    scanf("%d %d", &L, &M);
    for (int i = 0; i < M; i++) {
        scanf("%d %d", &range[i][0], &range[i][1]);
    }

    // sort and 'merge' range
    sort(range.begin(), range.begin() + M);
    int j = 0;
    for (int i = 1; i < M; i++) {
        // merge
        if (range[i][0] <= range[j][1]) {
            range[j][1] = max(range[i][1], range[j][1]);
        } else {
            L -= (range[j][1] - range[j][0] + 1);
            j = i;
        }
    }

    L -= (range[j][1] - range[j][0]);
    // printf("%d\n", j);
    // for (int i = 0; i <= j; i++) {
    //     printf("%d %d\n", range[i][0], range[i][1]);
    // }
    printf("%d", L);
    
    return 0;
}
