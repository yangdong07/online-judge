// P1515 旅行
// https://www.luogu.org/problemnew/show/P1515

#include <cstdio>
#include <algorithm>

using namespace std;

#define MAX_N 40

int main()
{
    int hotels[MAX_N] = { 0, 990, 1010, 1970, 2030, 2940, 3060, 3930, 4060, 4970, 5030, 5990, 6010, 7000 };
    int nHotel = 14;
    int minTrip, maxTrip;
    int n, i, j;
    scanf("%d %d %d", &minTrip, &maxTrip, &n);
    for (i = 0; i < n; ++i)
        scanf("%d", &hotels[nHotel + i]);
    nHotel += i;
    sort(hotels, hotels + nHotel);

    int dp[MAX_N], distance;
    dp[nHotel - 1] = 1;
    for (i = nHotel - 2; i >= 0; --i)
    {
        dp[i] = 0;
        for (j = i + 1; j < nHotel; ++j) {
            distance = hotels[j] - hotels[i];
            if (distance > maxTrip) break;
            else if (distance >= minTrip) dp[i] += dp[j];
        }
    }
    printf("%d", dp[0]);

}