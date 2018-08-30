// P2006 赵神牛的游戏
// https://www.luogu.org/problemnew/show/P2006

#include <iostream>

using namespace std;

#define MAX_N 30002

int main()
{
    long long mana, skills, health;
    long long cost, damage;
    bool kill = false;

    cin >> mana >> skills >> health;

    for (int i = 1; i <= skills; ++i)
    {
        cin >> cost >> damage;
        if (cost == 0)
        {
            if (damage > 0)
            {
                cout << (kill ? " " : "") << i;
                kill = true;
            }
        }
        else if (mana / cost * damage >= health)
        {
            cout << (kill ? " " : "") << i;
            kill = true;
        }
    }

    if (!kill)
        cout << -1;
}