# 61C Spring 2022 Project 2: CS61Classify

Spec: [https://cs61c.org/sp22/projects/proj2/](https://cs61c.org/sp22/projects/proj2/)



If you want to spare space for stack which can be easily accessed, you can do something like this:

```risc-v
    addi sp, sp, -16
    sw   s0, 8(sp)
    sw   s1, 12(sp)
```

Now you can easily access the `0(sp)` and `4(sp)`