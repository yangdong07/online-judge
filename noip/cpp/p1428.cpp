// P1428 小鱼比可爱
// https://www.luogu.org/problemnew/show/P1428

#include <cstdio>

#define MAX_N 100

int main()
{
    int n, lovely[MAX_N], i;
    scanf("%d", &n);
    for (i = 0; i < n; ++i)
        scanf("%d", &lovely[i]);
    
    int count, j;  // count left less lovely;
    printf("0");  // first no left;
    for (i = 1; i < n; ++i)
    {
        count = 0;
        for (j = 0; j < i; ++j) 
            if (lovely[j] < lovely[i]) count++;
        printf(" %d", count);
    }
}