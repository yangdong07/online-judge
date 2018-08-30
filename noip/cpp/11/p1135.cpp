// P1135 奇怪的电梯
// https://www.luogu.org/problemnew/show/P1135

#include <iostream>
#include <queue>

using namespace std;

const int MAX_N = 201;

int n, a, b;  // n floor, a start, b target
int k[MAX_N], v[MAX_N]; // k: can reach, v: visit

int bfs(int start, int target)
{
    queue<int> q;
    v[start] = 0;
    q.push(start);

    int t;

    while (!q.empty())
    {
        int p = q.front();
        q.pop();
        if (p == target) return v[p];
        // printf("%d %d\n", v[p], p);

        t = p - k[p];
        if (t > 0 && v[t] == -1)
        {
            v[t] = v[p] + 1;
            q.push(t);
        }
        t = p + k[p];
        if (t <= n && v[t] == -1)
        {
            v[t] = v[p] + 1;
            q.push(t);
        }
    }
    return -1;
}

int main()
{

    cin >> n >> a >> b;

    for (int i = 1; i <= n; ++i)
    {
        cin >> k[i];
        v[i] = -1;
    }
    
    cout << bfs(a, b) << endl;

    return 0;
}