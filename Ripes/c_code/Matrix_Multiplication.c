#include <stdio.h>
#define N 8  // 矩陣大小，可調整

int A[N][N], B[N][N], C[N][N];

void matrix_multiply() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            C[i][j] = 0;  // 初始化結果矩陣
            for (int k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

int main() {
    // 初始化矩陣 A 和 B
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i][j] = 1;
            B[i][j] = 1;
        }
    }

    matrix_multiply();  // 執行矩陣乘法

    printf("Matrix multiplication completed.\n");
    return 0;
}
