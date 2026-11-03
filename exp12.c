#include <stdio.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

int main() {
    int n, W;
    int wt[100], val[100];
    int dp[101][1001];

    printf("Enter number of items: ");
    scanf("%d", &n);

    printf("Enter weights:\n");
    for (int i = 1; i <= n; i++) {
        scanf("%d", &wt[i]);
    }

    printf("Enter profits:\n");
    for (int i = 1; i <= n; i++) {
        scanf("%d", &val[i]);
    }

    printf("Enter knapsack capacity: ");
    scanf("%d", &W);

    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= W; w++) {

            if (i == 0 || w == 0)
                dp[i][w] = 0;

            else if (wt[i] <= w) {
                dp[i][w] = max(
                    val[i] + dp[i-1][w-wt[i]],
                    dp[i-1][w]
                );
            }

            else
                dp[i][w] = dp[i-1][w];
        }
    }

    printf("Maximum Profit: %d\n", dp[n][W]);

    return 0;
}