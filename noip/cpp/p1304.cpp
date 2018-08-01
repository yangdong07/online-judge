// P1304 哥德巴赫猜想
// https://www.luogu.org/problemnew/show/P1304

#include <cstdio>
#include <cstring>

#define MAX_N 10000

bool isPrime[MAX_N];

// 埃拉托斯特尼筛法
void sieveOfEratosthenes(int n)
{
    memset(isPrime, true, sizeof(isPrime));
    for (int i = 2; i < n; ++i)
        if (isPrime[i])
            for (int j = i + i; j < n; j += i)
                isPrime[j] = false;
}

// 哥德巴赫猜想
void findGoldBachConjection(int n)
{
    for (int i = 2; i <= n / 2; ++i)
        if (isPrime[i] && isPrime[n - i]) {
            printf("%d=%d+%d\n", n, i, n - i);
            return;
        }
}

int main()
{
    int n;
    scanf("%d", &n);
    sieveOfEratosthenes(n);
    for (int i = 4; i <= n; i += 2)
        findGoldBachConjection(i);
}