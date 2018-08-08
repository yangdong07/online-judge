// P1583 魔法照片
// https://www.luogu.org/problemnew/show/P1583

#include <iostream>
#include <algorithm>

using namespace std;

struct people
{
    int number;   //编号
    int weight;   //权值
};

int cmp(const people &a, const people &b)
{
    if (a.weight != b.weight)
        return a.weight > b.weight;
    return a.number < b.number;
}


int main()
{
    int n, k, i;
    cin >> n >> k;

    people p[200010];
    int e[12]; // weight for category

    for (i = 0; i < 10; ++i)
        cin >> e[i];
    for (i = 0; i < n; ++i)
    {
        cin >> p[i].weight;
        p[i].number = i + 1;
    }

    sort(p, p + n, cmp);

    for (i = 0; i < n; i++)
        p[i].weight += e[i % 10];

    sort(p, p + n, cmp);
    for (i = 0; i < k; ++i)
        cout << p[i].number << " ";

}