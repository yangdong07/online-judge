// P1071 潜伏者
// https://www.luogu.org/problemnew/show/P1071

#include <iostream>
#include <cstring>

using namespace std;


char encode[26];
char decode[26];

bool check_code(string s, string o)
{
    int c, i, count = 0;
    memset(encode, 0, sizeof(encode));
    memset(decode, 0, sizeof(decode));
    for (i = 0; i < o.size(); ++i)
    {
        c = o[i] - 'A';
        if (!encode[c])
        {
            encode[c] = s[i];
            count++;
        }
        else if (encode[c] != s[i])
            return false;

        c = s[i] - 'A';
        if (!decode[c])
            decode[c] = o[i];
        else if (decode[c] != o[i])
            return false;
    }

    return count == 26;

}

int main()
{
    string s;
    string secret, plain; // 密文， 明文
    cin >> secret >> plain >> s;

    if (check_code(secret, plain))
        for (int i = 0; i < s.size(); ++i)
            cout << decode[s[i] - 'A'];
    else
        cout << "Failed";

    return 0;
}