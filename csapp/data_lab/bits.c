/* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.


EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
//1
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {
  return ~(~(x&~y)&~(~x&y));
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {

  /* 0x80 is the smallest 8 bit number with the MSB(most significant bit) set to 1 */ 
  /* 0x80 << 24 is the smallest 32 bit number with the MSB set to 1 */ 

  return 0x80 << 24;

}
//2
/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
#define toBool(x) (!!(x))
#define equal(x, y) (!(x^y))
int isTmax(int x) {
  x = ~x;
  return equal(negate(x),x) & toBool(x);
}
/* 
 * allOddBits - return 1 if all odd-numbered bits in word set to 1
 *   where bits are numbered from 0 (least significant) to 31 (most significant)
 *   Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allOddBits(int x) {
  
  /* 0xAA is 10101010 in binary */
  /* 0xAA << 8 is 10101010 00000000 */
  /* 0xAA << 16 is 10101010 00000000 00000000 */
  /* 0xAA << 24 is 10101010 00000000 00000000 00000000 */
  /* 0xAAAAAAAA is 10101010 10101010 10101010 10101010 */
  int mask = 0xAA | (0xAA << 8);
  mask = mask | (mask << 16);
  return equal(mask&x,mask);
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
  /* First, we negate x using bitwise not (~) */
  int negated_x = ~x;
  /* Then we add one to the negated x */
  return negated_x+1;
}
//3
/* 
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
#define less_positive(x, y) (toBool((((x) + negate(y)) & tmin())))
int isAsciiDigit(int x) {
  return equal(x >> 4, 0x3) & less_positive(x & 0xf, 0xA);
}
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
  // negate(1) 1111 1111
  int flag = negate(toBool(x));
  return (flag & y) | (~flag & z);
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
inline static int less(int x, int y) {

  #define flagx ( x & tmin())
  #define flagy ( y & tmin())
  #define notE (flagx ^ flagy)

    // if x is negative and y is positive, then x < y, else use less_positive
  return conditional(notE, flagx >> 31, less_positive(x, y));
}

int isLessOrEqual(int x, int y) {
  return less(x, y) | equal(x, y);
}
//4
/* 
 * logicalNeg - implement the ! operator, using all of 
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int logicalNeg(int x) {
  int tmp = x | (~x + 1);
  // right shifts arithmetically
  // 1111 1100 >> 1 = 1111 1110
  int tmp2 = tmp >> 31; 
  return tmp2 + 1;

}
/* howManyBits - return the minimum number of bits required to represent x in
 *             two's complement
 *  Examples: howManyBits(12) = 5
 *            howManyBits(298) = 10
 *            howManyBits(-5) = 4
 *            howManyBits(0)  = 1
 *            howManyBits(-1) = 1
 *            howManyBits(0x80000000) = 32
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 90
 *  Rating: 4
 */
int howManyBits(int x) {
   // explain -5 = 4
   // first, start with binary representation of 5: "0101"
   // then, negate it: "1010"
   // then, add 1: "1011"
   // the result is 4 bits

   // explain 12 = 5
    // first, start with binary representation of 12: "1100"
    // then, add sign bit '0'
    // the result is 5 bits
    
    // not negate(x)
   x = conditional(x & tmin(), ~x, x);

    int bit16 = (toBool((x >> 16)) << 4);  // determine if high 16 bits have 1
    x = x >> bit16;                        // if yes, low 16 bits are discarded

    int bit8 = (toBool((x >> 8)) << 3);  // determine if high 8 bits have 1
    x = x >> bit8;                       // if yes, low 8 bits are discarded

    int bit4 = (toBool((x >> 4)) << 2);  
    x = x >> bit4;                       

    int bit2 = (toBool((x >> 2)) << 1);  
    x = x >> bit2;                       

    int bit1 = (toBool((x >> 1)) << 0);  
    x = x >> bit1;                       

    int bit0 = (toBool(x));
    return bit16 + bit8 + bit4 + bit2 + bit1 + bit0 + 1;
}
//float
/* 
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned floatScale2(unsigned uf) {

  unsigned s = uf & (1 << 31);
  unsigned exp = (uf & 0x7f800000) >> 23;
  unsigned frac = uf & 0x007fffff;

  if (exp == 0) return s | (frac << 1);
  if (exp == 255) return uf;
  exp++;
  if (exp == 255) return s | 0x7f800000;

  return s | (exp << 23) | frac;
}
/* 
 * floatFloat2Int - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
int floatFloat2Int(unsigned uf) {
  // uf is like "0x40000000" ,"0x40490fdb"(3.14159274)
  unsigned s = uf & (1 << 31);
  unsigned exp = (uf & 0x7f800000) >> 23;
  unsigned frac = uf & 0x007fffff;

  // inf: exp = 255, frac = 0
  // NaN: exp = 255, frac != 0

  int E = exp - 127;
  if (exp == 255 || E > 31) return 0x80000000u;
  if (E < 0) return 0;

  unsigned M = frac | (1 << 23); // frac + 1
  // E compare to 23 because M is decimal
  int V = (E > 23 ? M << (E - 23) : M >> (23 - E));

  if (s) V *= -1;

  return V;
}
/* 
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 * 
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. Also if, while 
 *   Max ops: 30 
 *   Rating: 4
 */
unsigned floatPower2(int x) {
  // E = e - 127 (-126 ~ 127)
  // V = 1 * 2^E
  // x it the E
  // the maximum finite positive number has an exponent of 127.
  if (x >= 128) return 0x7f800000;
  // the minimum finite positive number has an exponent of -126.
  if (x >= -126) return (x + 127) << 23;
  // -150 < x < -126 , remain 23 bits
  if (x >= -150) 
  {
    return 1 << (x + 150);
  } else {
    return 0;
  }
}
