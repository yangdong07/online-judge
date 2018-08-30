// P1781 宇宙总统
// https://www.luogu.org/problemnew/show/P1781

#include <iostream>
#include <string>

using namespace std;

int main()
{
    int n, i;
    cin >> n;

    string votes, max_votes = "";
    int index;  // record index of max votes

    for (i = 1; i <= n; i++)
    {
        cin >> votes;
        if (votes.length() > max_votes.length()
            || (votes.length() == max_votes.length() && votes > max_votes))
        {
            max_votes = votes;
            index = i;
        }
    }
    cout << index << endl << max_votes << endl;
    return 0;
}