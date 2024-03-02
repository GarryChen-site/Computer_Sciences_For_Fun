.globl matmul

.text
# =======================================================
# FUNCTION: Matrix Multiplication of 2 integer matrices
#   d = matmul(m0, m1)
# Arguments:
#   a0 (int*)  is the pointer to the start of m0
#   a1 (int)   is the # of rows (height) of m0
#   a2 (int)   is the # of columns (width) of m0
#   a3 (int*)  is the pointer to the start of m1
#   a4 (int)   is the # of rows (height) of m1
#   a5 (int)   is the # of columns (width) of m1
#   a6 (int*)  is the pointer to the the start of d
# Returns:
#   None (void), sets d = matmul(m0, m1)
# Exceptions:
#   Make sure to check in top to bottom order!
#   - If the dimensions of m0 do not make sense,
#     this function terminates the program with exit code 38
#   - If the dimensions of m1 do not make sense,
#     this function terminates the program with exit code 38
#   - If the dimensions of m0 and m1 don't match,
#     this function terminates the program with exit code 38
# =======================================================
matmul:
    # Error checks
    li      t0, 1
    blt     a1, t0, error
    blt     a2, t0, error
    blt     a4, t0, error
    blt     a5, t0, error
    bne     a2, a4, error
    # Prologue
    addi    sp, sp, -4
    sw      s0, 0(sp)
    # init
    mv      t0, x0 # set row number to zero
    mv      s0, x0 # set column number to zero
    mv      t6, x0 
outer_loop:
    mv      t1, x0 # set inner counter to zero
    mv      t6, x0 # sum
    mul     t2, a2, t0 # get row memory bias
    slli    t2, t2, 2 # 4 bytes per element
    add     t2, a0, t2 # get outer pointer address
inner_loop:
    # access m1 element
    mul     t3, a5, t1 # step stride
    add     t3, t3, s0 # column bias added
    slli    t3, t3, 2 # 4 bytes per element
    add     t3, a3, t3 # get inner element address
    lw      t5, 0(t3)
    # access m0 element
    slli    t3, t1, 2 # 4 bytes per element
    add     t3, t2, t3 # get outer element address
    lw      t4, 0(t3)
    mul     t4, t5, t4 # store result in t4
    # store element
    add     t6, t6, t4
    # check inner loop condition
    addi    t1, t1, 1
    bge     t1, a2, inner_end
    j       inner_loop
inner_end:
    # get bias for output pointer
    mul     t4, a5, t0
    slli    t4, t4, 2
    # get current access memory address
    slli    t5, s0, 2
    add     t5, a6, t5
    add     t5, t5, t4 # add bias
    sw      t6, 0(t5)
    # reset temp sum
    mv      t6, x0
    # check if need clear column number
    addi    s0, s0, 1
    bge     s0, a5, clear_col_num
    j       outer_loop
clear_col_num:
    mv      s0, x0
outer_end:
    # check outer loop condition
    addi    t0, t0, 1
    bge     t0, a1, out
    j       outer_loop
out:
    lw      s0, 0(sp)
    addi    sp, sp, 4
    ret
error:
    li      a0, 38
    j       exit



# possible C code

; #include <stdio.h>

; void matmul(int a1, int a2, int a4, int a5, int* a0, int* a3, int* a6) {
;     // Error checks
;     if (a1 < 1 || a2 < 1 || a4 < 1 || a5 < 1 || a2 != a4) {
;         printf("Error: Invalid matrix dimensions.\n");
;         exit(38);
;     }

;     // Initialize row and column numbers
;     int row = 0;
;     int col = 0;

;     // Outer loop over rows of first matrix and columns of second matrix
;     for (row = 0; row < a1; row++) {
;         // Inner loop over elements of current row of first matrix and current column of second matrix
;         for (col = 0; col < a5; col++) {
;             int sum = 0;
;             for (int i = 0; i < a2; i++) {
;                 // Access elements of first and second matrices
;                 int element1 = a0[row * a2 + i];
;                 int element2 = a3[i * a5 + col];
;                 // Multiply elements and add to sum
;                 sum += element1 * element2;
;             }
;             // Store sum in result matrix
;             a6[row * a5 + col] = sum;
;         }
;     }
; }