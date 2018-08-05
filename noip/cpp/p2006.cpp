// P2006 赵神牛的游戏
// https://www.luogu.org/problemnew/show/P2006

#include <iostream>

using namespace std;

#define MAX_N 30000

int main()
{
    long mana, skills, health;
    long cost, damage;
    bool kill = false;

    cin >> mana >> skills >> health;

    for (int i = 1; i <= skills; ++i)
    {
        cin >> cost >> damage;
        if (mana / cost * damage >= health)
        {
            cout << i << " ";
            kill = true;
        }
    }

    if (!kill)
        cout << -1;
}