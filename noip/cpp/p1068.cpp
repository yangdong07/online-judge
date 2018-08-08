// P1068 分数线划定
// https://www.luogu.org/problemnew/show/P1068

#include <iostream>
#include <algorithm>

using namespace std;

#define MAX_N 5001

typedef struct
{
    int id;
    int score;
} Man;

bool cmp(const Man& a, const Man& b)
{
    if (a.score == b.score)
        return a.id < b.id;
    return a.score > b.score;
}

int main()
{
    int n, m, i;
    Man a[MAX_N];
    cin >> n >> m;
    for (i = 1; i <= n; ++i)
        cin >> a[i].id >> a[i].score;

    sort(a + 1, a + n + 1, cmp);

    int mp = m * 3 / 2;
    int score = a[mp].score;
    for ( ; mp < n && a[mp + 1].score >= score; ++mp) ;

    cout << score << " " << mp << endl;

    for (i = 1; i <= mp; ++i)
        cout << a[i].id << " " << a[i].score << endl;

}