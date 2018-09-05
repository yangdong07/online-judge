/*
ID: yesimim1
TASK: preface
LANG: C++

#include <cstdio>
    FILE *fin = fopen ("preface.in", "r");
    FILE *fout = fopen ("preface.out", "w");

#include <fstream>
    ofstream fout ("preface.out");
    ifstream fin ("preface.in");
*/

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

string roman_dict[4][10] = {
    {"", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"},
    {"", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"},
    {"", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM"},
    {"", "M", "MM", "MMM"}};

string roman_c = "IVXLCDM";

string roman_number(int n)
{
    string s = "";
    for (int t = n, i = 0; t; t /= 10, ++i)
        s = roman_dict[i][t % 10] + s;
    return s;
}

int main()
{
    ofstream fout ("preface.out");
    ifstream fin ("preface.in");

    int n;
    fin >> n;

    string rn;
    int count[26] = {0};

    for (int i = 1; i <= n; i++)
    {
        rn = roman_number(i);
        for (size_t j = 0; j < rn.size(); ++j)
            count[rn[j] - 'A']++;
    }

    string::iterator it;
    for (it = roman_c.begin(); it != roman_c.end(); ++it)
    {
        if (count[*it - 'A'])
            fout << *it << " " << count[*it - 'A'] << endl;;
    }
    return 0;
}