#include <stdio.h>
#include <string.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

int main() {
    char a[100], b[100];
    int dp[101][101];

    printf("Enter first string: ");
    scanf("%99s", a);

    printf("Enter second string: ");
    scanf("%99s", b);

    int m = strlen(a);
    int n = strlen(b);

    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {

            if (i == 0 || j == 0)
                dp[i][j] = 0;

            else if (a[i-1] == b[j-1])
                dp[i][j] = 1 + dp[i-1][j-1];

            else
                dp[i][j] = max(dp[i-1][j],
                               dp[i][j-1]);
        }
    }

    printf("Length of LCS: %d\n", dp[m][n]);

    return 0;
}