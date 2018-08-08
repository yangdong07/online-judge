// P1093 奖学金
// https://www.luogu.org/problemnew/show/P1093

#include <iostream>
#include <algorithm>

using namespace std;

struct student
{
    int id;    //编号
    int s1;    //语文
    int s2;    //数学
    int s3;    //英语
    int score; //总分
};

bool cmp(const student &a, student &b)
{
    // 先比总分
    if (a.score != b.score)
        return a.score > b.score;

    // 再比语文
    if (a.s1 != b.s1)
        return a.s1 > b.s1;

    // 最后是学号
    return a.id < b.id;
}

int main()
{
    int n, i;
    student stu[310];
    cin >> n;
    for (i = 0; i < n; i++)
    {
        stu[i].id= i + 1;            
        cin >> stu[i].s1 >> stu[i].s2 >> stu[i].s3;
        stu[i].score = stu[i].s1 + stu[i].s2 + stu[i].s3;
    }
    sort(stu, stu + n, cmp);
    for (i = 0; i < 5; i++)
        cout << stu[i].id << ' ' << stu[i].score << endl;
    return 0;
}