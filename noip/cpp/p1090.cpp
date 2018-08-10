// P1090 合并果子
// https://www.luogu.org/problemnew/show/P1090

#include <iostream>
#include <queue>

using namespace std;

int main()
{
    priority_queue<int> heap;

    int n, i, w; // w for weight;
    cin >> n;

    for (i = 0; i < n; ++i)
    {
        cin >> w;
        heap.push(-w);  // min weight, max -weight
    }

    int a, b;
    int cost = 0;
    while (heap.size() >= 2)
    {
        a = heap.top();
        heap.pop();
        b = heap.top();
        heap.pop();
        cost += (a + b);
        heap.push(a + b);
    }

    cout << -cost << endl;
    return 0;
}