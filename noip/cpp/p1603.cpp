// P1603 斯诺登的密码
// https://www.luogu.org/problemnew/show/P1603

#include <iostream>
#include <iomanip>
#include <map>
#include <algorithm>

using namespace std;

#define MAX_N 100

map<string, int> dict;

void init_dict()
{
    dict["zero"] = 0;
    dict["one"] = 1;
    dict["two"] = 2;
    dict["three"] = 3;
    dict["four"] = 4;
    dict["five"] = 5;
    dict["six"] = 6;
    dict["seven"] = 7;
    dict["eight"] = 8;
    dict["nine"] = 9;
    dict["ten"] = 10;
    dict["eleven"] = 11;
    dict["twelve"] = 12;
    dict["thirteen"] = 13;
    dict["fourteen"] = 14;
    dict["fifteen"] = 15;
    dict["sixteen"] = 16;
    dict["seventeen"] = 17;
    dict["eighteen"] = 18;
    dict["nineteen"] = 19;
    dict["twenty"] = 20;
    dict["a"] = 1;
    dict["both"] = 2;
    dict["another"] = 1;
    dict["first"] = 1;
    dict["second"] = 2;
    dict["third"] = 3;
}

int main()
{
    init_dict();

    int i, j;
    string s;
    int square, nums[MAX_N];
    for (i = 0, j = 0; i < 6; ++i)
    {
        cin >> s;
        if (dict.count(s))
        {
            square = dict[s] * dict[s];
            for (; square; square /= 100)
                nums[j++] = square % 100;
        }
    }
    sort(nums, nums + j);

    cout << (j > 0 ? nums[0] : 0);

    for (i = 1; i < j; ++i)
        cout << setfill('0') << setw(2) << nums[i];
     return 0;
}