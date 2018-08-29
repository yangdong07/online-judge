
#include <cstdio>
#include <cmath>

#define PI 3.14159265

int josephus(int n, int k)
{
  if (n == 1)
    return 1;
  else
    /* The position returned by josephus(n - 1, k) is adjusted because the
       recursive call josephus(n - 1, k) considers the original position 
       k%n + 1 as position 1 */
    return (josephus(n - 1, k) + k - 1) % n + 1;
}

int josephus_friend(int n, int k)
{
  if (n == 2)
    return 1;
  else
    return (josephus_friend(n - 1, k) + k - 1) % n + 1;
}

void test_abc(double A)
{
  double B = (180.0 - 2.0 * A) / 3.0; // 2A + 3B = 180
  double C = 180.0 - A - B;

  double a = 1.0;
  double b = a / sin(A * PI / 180.0) * sin(B * PI / 180.0);
  double c = a / sin(A * PI / 180.0) * sin(C * PI / 180.0);

  printf("%lf, %lf, %lf\n", A, B, C);
  printf("%lf, %lf, %lf\n", a, b, c);
  printf("%lf, %lf, %lf\n", a * a, b * b, c * c);
  printf("%lf, %lf\n", c * c - a * c, b * b);
}

// Driver Program to test above function
int main()
{
  for (double i = 1.0; i < 90.0; i += 1.0)
    test_abc(i);
  // int n = 41;
  // int k = 3;
  // printf("The chosen place is %d", josephus_friend(n, k));
  return 0;
}