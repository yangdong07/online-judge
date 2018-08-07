// P1036 选数
// https://www.luogu.org/problemnew/show/P1036

#include <iostream>
#include <cmath>

using namespace std;

int n, k;
int nums[30];
int n_primes = 0;

bool is_prime(int n)
{
    for (int i = 2; i < sqrt(n); ++i)
        if (n % i == 0) return false;
    return true;
}

void dfs(int i, int depth, int sum)
{
    if (depth == k)
    {
        if (is_prime(sum)) n_primes++;
        return;
    }
    for (int j = i; j < n; ++j)
        dfs(j + 1, depth + 1, sum + nums[j]);
}

int main()
{
    cin >> n >> k;
    for (int i = 0; i < n; ++i)
        cin >> nums[i];
    
    n_primes = 0;

    dfs(0, 0, 0);

    cout << n_primes;
}