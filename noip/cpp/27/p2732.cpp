
// P2732 商店购物 Shopping Offers
// https://www.luogu.org/problemnew/show/P2732

#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAX_N = 5;
const int MAX_NUM = 6;
const int BASE = 6;         // 0,1,2,3,4,5
const int MAX_STATE = 7777; // MAX_STATE = 6^5 + 1
const int MAX_COMB = 100;
const int MAX_ID = 1000;    // 1 <= id <= 999

struct Combination
{
    int n;
    int id[MAX_N];
    int num[MAX_N];
    int ds;   // reduce state;
    int price;
};

int comb_to_num(int c[MAX_N], int base = BASE)
{
    int num = 0;
    for (int i = MAX_N - 1; i >= 0; --i)
        num = num * base + c[i];
    return num;
}

void num_to_comb(int num, int c[MAX_N], int base = BASE)
{
    for (int i = 0; i < MAX_N; ++i, num /= base)
        c[i] = num % base;
}

bool valid(int a, int b, int base = BASE)
{
    for (; b; a /= base, b /= base)
        if (a % base < b % base)
            return false;
    return true;
}

int main()
{
    int n_combs, i, j;
    Combination comb[MAX_COMB];

    scanf("%d", &n_combs);
    for (i = 0; i < n_combs; ++i)
    {
        scanf("%d", &comb[i].n);
        for (j = 0; j < comb[i].n; ++j)
            scanf("%d %d", &comb[i].id[j], &comb[i].num[j]);
        scanf("%d", &comb[i].price);
    }

    // for (i = 0; i < n_combs; ++i)
    // {
    //     printf("%d ", comb[i].n);
    //     for (j = 0; j < comb[i].n; ++j)
    //         printf("%d %d ", comb[i].id[j], comb[i].num[j]);
    //     printf("%d\n", comb[i].price);
    // }

    int n, id;
    int idx[MAX_ID] = {0};
    int price[MAX_N], num[MAX_N] = {0};
    scanf("%d", &n);

    for (i = 0; i < n; ++i)
    {
        scanf("%d", &id);
        idx[id] = i + 1;
        scanf("%d %d", &num[i], &price[i]);
    }

    // process combinations
    int dn[MAX_N];
    for (i = 0; i < n_combs; ++i)
    {
        memset(dn, 0, sizeof(dn));
        for (j = 0; j < comb[i].n; ++j)
            dn[idx[comb[i].id[j]] - 1] = comb[i].num[j];
        comb[i].ds = comb_to_num(dn);
        // printf("%d\n", comb[i].ds);
    }

    // process dp
    int dp[MAX_STATE], buy[MAX_N];
    int n_state = 1;
    for (i = 0; i < n; ++i) n_state *= MAX_NUM;

    for (i = 0; i < n_state; ++i)
    {
        dp[i] = 0;
        num_to_comb(i, buy);
        for (j = 0; j < n; ++j)
            dp[i] += buy[j] * price[j];
    }
    // for (i = 0; i < n_state; ++i)
    //     printf("%-3d", i);
    // printf("\n");
    // for (i = 0; i < n_state; ++i)
    //     printf("%-3d", i % 6);
    // printf("\n");
    // for (i = 0; i < n_state; ++i)
    //     printf("%-3d", i / 6);
    // printf("\n");
    // for (i = 0; i < n_state; ++i)
    //     printf("%-3d", dp[i]);
    // printf("\n");

    for (i = 0; i < n_combs; ++i)
        for (j = comb[i].ds; j <= n_state; ++j)
            if (valid(j, comb[i].ds))
                dp[j] = min(dp[j], dp[j - comb[i].ds] + comb[i].price);

    // for (i = 0; i < n_state; ++i)
    //     printf("%-3d", dp[i]);
    // printf("\n");

    printf("%d\n", dp[comb_to_num(num)]);
    
    return 0;
}