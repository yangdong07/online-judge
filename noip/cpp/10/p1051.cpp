// P1051 谁拿了最多奖学金
// https://www.luogu.org/problemnew/show/P1051

#include <cstdio>
#include <cstring>

/*
 院士奖学金，每人 8000 元，期末平均成绩高于 80 分（ >80 ），并且在本学期内发表 1 篇或 1 篇以上论文的学生均可获得；
 五四奖学金，每人 4000 元，期末平均成绩高于 85 分（ >85 ），并且班级评议成绩高于 80 分（ >80 ）的学生均可获得；
 成绩优秀奖，每人 2000 元，期末平均成绩高于 90 分（ >90 ）的学生均可获得；
 西部奖学金，每人 1000 元，期末平均成绩高于 85 分（ >85 ）的西部省份学生均可获得；
 班级贡献奖，每人 850 元，班级评议成绩高于 80 分（ >80 ）的学生干部均可获得；
*/
int bonus(int score1, int score2,
          bool is_leader, bool from_west, int papers)
{
    int money = 0;
    if (score1 > 80 && papers >= 1)
        money += 8000;
    
    if (score1 > 85 && score2 > 80)
        money += 4000;

    if (score1 > 90)
        money += 2000;

    if (score1 > 85 && from_west)
        money += 1000;

    if (score2 > 80 && is_leader)
        money += 850;

    return money;
}

int main()
{
    int n, i;
    scanf("%d", &n);

    char name[25], winner[25];
    int score1, score2, papers;
    char is_leader, from_west;
    int money, max_money = 0, total = 0;

    for (i = 0; i < n; ++i)
    {
        scanf("%s %d %d %c %c %d", name,
              &score1, &score2, &is_leader, &from_west, &papers);
        money = bonus(score1, score2, is_leader == 'Y', from_west == 'Y', papers);
        total += money;

        if (money > max_money)
        {
            strcpy(winner, name);
            max_money = money;
        }
    }

    printf("%s\n%d\n%d\n", winner, max_money, total);

}