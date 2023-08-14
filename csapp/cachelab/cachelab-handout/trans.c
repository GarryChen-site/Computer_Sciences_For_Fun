/* 
 * trans.c - Matrix transpose B = A^T
 *
 * Each transpose function must have a prototype of the form:
 * void trans(int M, int N, int A[N][M], int B[M][N]);
 *
 * A transpose function is evaluated by counting the number of misses
 * on a 1KB direct mapped cache with a block size of 32 bytes.
 */ 
#include <stdio.h>
#include "cachelab.h"

int is_transpose(int M, int N, int A[N][M], int B[M][N]);

/* 
 * transpose_submit - This is the solution transpose function that you
 *     will be graded on for Part B of the assignment. Do not change
 *     the description string "Transpose submission", as the driver
 *     searches for that string to identify the transpose function to
 *     be graded. 
 */
char transpose_submit_desc[] = "Transpose submission";
void solve_32(int M, int N, int A[N][M], int B[M][N]);
void solve_64(int M, int N, int A[N][M], int B[M][N]);
void solve_61(int M, int N, int A[N][M], int B[M][N]);
void transpose_submit(int M, int N, int A[N][M], int B[M][N])
{
    //     int i, j, tmp;

    // for (i = 0; i < N; i++) {
    //     for (j = 0; j < M; j++) {
    //         tmp = A[i][j];
    //         B[j][i] = tmp;
    //     }
    // }   
    switch (M) {
        case 32:
            solve_32(M, N, A, B);
            break;
        case 64:
            solve_64(M, N, A, B);
            break;
        case 61:
            solve_61(M, N, A, B);
            break;
    }
}

void solve_32(int M, int N, int A[N][M], int B[M][N]) {
    int i, j;

    for (i=0; i<N; i+=8) {
        for (j=0; j<M; j+=8) {

            for (int cnt =0; cnt <8; ++cnt, ++i) {
                int temp1 = A[i][j];
                int temp2 = A[i][j+1];
                int temp3 = A[i][j+2];
                int temp4 = A[i][j+3];
                int temp5 = A[i][j+4];
                int temp6 = A[i][j+5];
                int temp7 = A[i][j+6];
                int temp8 = A[i][j+7];

                B[j][i] = temp1;    
                B[j+1][i] = temp2;
                B[j+2][i] = temp3;
                B[j+3][i] = temp4;
                B[j+4][i] = temp5;
                B[j+5][i] = temp6;
                B[j+6][i] = temp7;
                B[j+7][i] = temp8;
            }
            // for next j loop
            i -= 8;
        }
    }
}

void solve_64(int M, int N, int A[N][M], int B[M][N]) {
    int i, j;

    for (i=0; i<N; i+=8) {
        for (j=0; j<M; j+=8) {
            int temp1, temp2, temp3, temp4, temp5, temp6, temp7, temp8, cnt;
            for (cnt = 0; cnt < 4; cnt++, i++) {
                // left top
                temp1 = A[i][j];
                temp2 = A[i][j+1];
                temp3 = A[i][j+2];
                temp4 = A[i][j+3];

                // right top
                temp5 = A[i][j+4];
                temp6 = A[i][j+5];
                temp7 = A[i][j+6];
                temp8 = A[i][j+7];

                B[j][i] = temp1;
                B[j+1][i] = temp2;
                B[j+2][i] = temp3;
                B[j+3][i] = temp4;

                // A right top -> B right top
                B[j][i+4] = temp5;
                B[j+1][i+4] = temp6;
                B[j+2][i+4] = temp7;
                B[j+3][i+4] = temp8;
            }
            i -= 4;
            for (cnt = 0; cnt < 4; j++, cnt++) {
                // A left bottom
                temp1 = A[i+4][j];
                temp2 = A[i+5][j];
                temp3 = A[i+6][j];
                temp4 = A[i+7][j];

                // B right top, i.e. A right top
                temp5 = B[j][i+4];
                temp6 = B[j][i+5];
                temp7 = B[j][i+6];
                temp8 = B[j][i+7];

                // A left bottom -> B right top
                B[j][i+4] = temp1;
                B[j][i+5] = temp2;
                B[j][i+6] = temp3;
                B[j][i+7] = temp4;

                // B right top -> B left bottom
                B[j+4][i] = temp5;
                B[j+4][i+1] = temp6;
                B[j+4][i+2] = temp7;
                B[j+4][i+3] = temp8;
            }
            for(i +=4, cnt =0; cnt < 4; cnt++, i++) {
                temp1 = A[i][j];
                temp2 = A[i][j+1];
                temp3 = A[i][j+2];
                temp4 = A[i][j+3];

                B[j][i] = temp1;
                B[j+1][i] = temp2;
                B[j+2][i] = temp3;
                B[j+3][i] = temp4;
            }
            i -= 8, j -= 4;
        }
    }
}

void solve_61(int M, int N, int A[N][M], int B[M][N]) {
    int i, j, ex;
    ex = 16;
    for (i=0; i<N; i+= ex) {
        for (j=0; j<M; j+= ex) {
            for (int x = i; x < i+ex && x < N; x++) {
                for (int y = j; y < j+ex && y < M; y++) {
                    B[y][x] = A[x][y];
                }
            }
        }
    }
}
/* 
 * You can define additional transpose functions below. We've defined
 * a simple one below to help you get started. 
 */ 

/* 
 * trans - A simple baseline transpose function, not optimized for the cache.
 */
char trans_desc[] = "Simple row-wise scan transpose";
void trans(int M, int N, int A[N][M], int B[M][N])
{
    int i, j, tmp;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            tmp = A[i][j];
            B[j][i] = tmp;
        }
    }    

}

/*
 * registerFunctions - This function registers your transpose
 *     functions with the driver.  At runtime, the driver will
 *     evaluate each of the registered functions and summarize their
 *     performance. This is a handy way to experiment with different
 *     transpose strategies.
 */
void registerFunctions()
{
    /* Register your solution function */
    registerTransFunction(transpose_submit, transpose_submit_desc); 

    /* Register any additional transpose functions */
    // registerTransFunction(trans, trans_desc); 

}

/* 
 * is_transpose - This helper function checks if B is the transpose of
 *     A. You can check the correctness of your transpose by calling
 *     it before returning from the transpose function.
 */
int is_transpose(int M, int N, int A[N][M], int B[M][N])
{
    int i, j;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; ++j) {
            if (A[i][j] != B[j][i]) {
                return 0;
            }
        }
    }
    return 1;
}

