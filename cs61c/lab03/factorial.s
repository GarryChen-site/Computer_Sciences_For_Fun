.globl factorial

.data
n: .word 3

.text
main:
    la t0, n
    lw a0, 0(t0)
    jal ra, factorial

    addi a1, a0, 0
    addi a0, x0, 1
    ecall # Print Result

    addi a1, x0, '\n'
    addi a0, x0, 11
    ecall # Print newline

    addi a0, x0, 10
    ecall # Exit

factorial:
    # YOUR CODE HERE
    addi t0, x0, 1
L1:
    beqz a0, L2 # if a0 == 0, jump to L2
    mul t0, t0, a0 # t0 = t0 * a0
    addi a0, a0, -1 # a0 = a0 - 1
    j L1 # jump to L1
L2:
    addi a0, t0, 0 # a0 = t0
    jr ra # return
