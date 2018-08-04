// P1909 买铅笔
// https://www.luogu.org/problemnew/show/P1909

#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
    int n, num, price;
    int min_cost;

    cin >> n;
    cin >> num >> price;
    min_cost = ((n - 1) / num + 1) * price;
    cin >> num >> price;
    min_cost = min(((n - 1) / num + 1) * price, min_cost);
    cin >> num >> price;
    min_cost = min(((n - 1) / num + 1) * price, min_cost);

    cout << min_cost;
}