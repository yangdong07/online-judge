// P1867 【Mc生存】经验值
// https://www.luogu.org/problemnew/show/P1867

#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
    int n, i;
    double health = 10.0, cost;
    int experience = 0, e;
    bool dead = false;

    cin >> n;

    for (i = 0; i < n; ++i)
    {
        cin >> cost >> e;
        if (dead) continue;
        dead = (cost >= health);
        if (!dead)
        {
            health = min(10.0, health - cost);
            experience += e;
        }
    }

    int level = 0, x = 1;
    while (experience >= x)
    {
        experience -= x;
        level++;
        x <<= 1;
    }
    cout << level << " " << experience;

}