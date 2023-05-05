from lab pdf

When functions hexmatch and strncmp are called, they push data onto the stack, overwriting portions of memory that held the buffer used by getbuf. As a result, you will need to be careful where you place the string representation of your cookie.

which means can not do like solution2, getbuf will be overwrite

the point is how to save the cookie(59b997fa) in a appropriate place

save to stack, 0x5561DC78 the start address of getbuf, add 8+40 bytes, so the addr is 0x5561DCa8

so, see solution3.s

and the ascii code of 59b997fa is 35 39 62 39 39 37 66 61 and with the null byte 00