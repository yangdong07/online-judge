// P1604 B进制星球
// https://www.luogu.org/problemnew/show/P1604

#include <cstdio>
#include <cstring>

const int MAX_N = 2010;
const int MAX_B = 37;
const int MAX_ASCII = 256;

char i2c[MAX_B];
int c2i[MAX_ASCII] = {0};

void init_ci()
{
    int i;
    for (i = 0; i < 10; ++i)
    {
        i2c[i] = i + '0';
        c2i[i + '0'] = i;
    }
    for (i = 10; i < MAX_B; ++i)
    {
        i2c[i] = 'A' + i - 10;
        c2i[i2c[i]] = i;
    }
}

void reverse(char s[], int n)
{
    char c;
    for (int i = 0, j = n - 1; i < j;)
    { c = s[i]; s[i++] = s[j]; s[j--] = c; }
}

// a += b;
int add(char a[], char b[], int base = 10)
{
    int l1 = strlen(a), l2 = strlen(b);
    // reverse
    reverse(a, l1);
    reverse(b, l2);

    // adding
    int i, carry = 0, sum;
    for (i = 0; i < l1 && i < l2; ++i)
    {
        sum = c2i[a[i]] + c2i[b[i]] + carry;
        a[i] = i2c[sum % base];
        carry = sum / base;
    }
    for (; i < l1 || i < l2; ++i)
    {
        sum = c2i[l1 < l2 ? b[i] : a[i]] + carry;
        a[i] = i2c[sum % base];
        carry = sum / base;
    }

    if (carry) a[i++] = i2c[carry];
    a[i] = '\0';
    reverse(a, i);
    return i;
}


int main()
{
    init_ci();

    int base;
    scanf("%d", &base);

    char a[MAX_N], b[MAX_N];
    scanf("%s %s", a, b);
    add(a, b, base);
    printf("%s", a);

    return 0;
}