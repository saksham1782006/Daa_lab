#include <stdio.h>
#include <stdlib.h>

#define MAX 64

void add(int n, int A[MAX][MAX], int B[MAX][MAX], int C[MAX][MAX]) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];
}

void subtract(int n, int A[MAX][MAX], int B[MAX][MAX], int C[MAX][MAX]) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] - B[i][j];
}

void strassen(int n, int A[MAX][MAX], int B[MAX][MAX],
              int C[MAX][MAX]) {

    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int k = n / 2;

    int A11[MAX][MAX] = {0}, A12[MAX][MAX] = {0};
    int A21[MAX][MAX] = {0}, A22[MAX][MAX] = {0};
    int B11[MAX][MAX] = {0}, B12[MAX][MAX] = {0};
    int B21[MAX][MAX] = {0}, B22[MAX][MAX] = {0};

    int M1[MAX][MAX] = {0}, M2[MAX][MAX] = {0};
    int M3[MAX][MAX] = {0}, M4[MAX][MAX] = {0};
    int M5[MAX][MAX] = {0}, M6[MAX][MAX] = {0};
    int M7[MAX][MAX] = {0};

    int T1[MAX][MAX] = {0};
    int T2[MAX][MAX] = {0};

    /* Divide matrices into 4 submatrices */
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + k];
            A21[i][j] = A[i + k][j];
            A22[i][j] = A[i + k][j + k];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + k];
            B21[i][j] = B[i + k][j];
            B22[i][j] = B[i + k][j + k];
        }
    }

    /* M1 = (A11 + A22)(B11 + B22) */
    add(k, A11, A22, T1);
    add(k, B11, B22, T2);
    strassen(k, T1, T2, M1);
    add(k, A21, A22, T1);
    strassen(k, T1, B11, M2);
    subtract(k, B12, B22, T2);
    strassen(k, A11, T2, M3);
    subtract(k, B21, B11, T2);
    strassen(k, A22, T2, M4);
    add(k, A11, A12, T1);
    strassen(k, T1, B22, M5);
    subtract(k, A21, A11, T1);
    add(k, B11, B12, T2);
    strassen(k, T1, T2, M6);
    subtract(k, A12, A22, T1);
    add(k, B21, B22, T2);
    strassen(k, T1, T2, M7);
    add(k, M1, M4, T1);
    subtract(k, T1, M5, T2);
    add(k, T2, M7, T1);
    add(k, M3, M5, T2);
    add(k, M2, M4, T2);
    subtract(k, M1, M2, T1);
    add(k, T1, M3, T2);
    add(k, T2, M6, T1);

    /* Combine submatrices */
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            C[i][j] = T1[i][j];              // C11
            C[i][j + k] = T2[i][j];           // temporary, corrected below
        }
    }

    /*
       Recalculate and store each quadrant correctly.
    */
    int C11[MAX][MAX] = {0}, C12[MAX][MAX] = {0};
    int C21[MAX][MAX] = {0}, C22[MAX][MAX] = {0};

    add(k, M1, M4, C11);
    subtract(k, C11, M5, C11);
    add(k, C11, M7, C11);

    add(k, M3, M5, C12);
    add(k, M2, M4, C21);

    subtract(k, M1, M2, C22);
    add(k, C22, M3, C22);
    add(k, C22, M6, C22);

    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            C[i][j] = C11[i][j];
            C[i][j + k] = C12[i][j];
            C[i + k][j] = C21[i][j];
            C[i + k][j + k] = C22[i][j];
        }
    }
}

int main() {
    int n;

    printf("Enter matrix size (power of 2): ");
    scanf("%d", &n);

    int A[MAX][MAX], B[MAX][MAX], C[MAX][MAX] = {0};

    printf("Enter elements of Matrix A:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &A[i][j]);

    printf("Enter elements of Matrix B:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &B[i][j]);

    strassen(n, A, B, C);

    printf("\nResult Matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            printf("%d ", C[i][j]);
        printf("\n");
    }

    return 0;
}
