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
/
  整数运算规则：
  2进制补码表示整数，整数32bit表示，且范围0~255（0xFF）之间
  算数右移最高位填充符号位
  移位量0~31之间
  可以使用的：& ^ | + << >> ! ~

  浮点数运算规则：
  可以使用循环和条件控制
  可以使用int和unsigned
  可以使用逻辑右移和算数右移

  最大操作数限制，=不计算在内
  dlc编译器检查代码合法性（满足限制条件）
  btest测试代码正确性
*/
#endif

//1------------------------------------------------------------
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {
  return ~(~(~x&y) & ~(x&~y));
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
  return 1<<31;
}
//2-----------------------------------------------------------
/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmax(int x) {
  return !(~((x+1)^x) + !(~x));
  //保证!~( ((x+1)^x) + !(~x) )第一个()里面是全1
  //或者!(~((x+1)^x) + !(~x))第一个()里面是全0
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
  
  int mask1 = (10 << 4) | 10;
  int mask2 = (mask1 << 8) | mask1;
  int mask3 = mask2  << 16 ;
  int mask = mask2 | mask3;
  return !((mask & x)^mask);
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {

  return ~x + 1;
}


//3--------------------------------------------------------------------
/* 
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int isAsciiDigit(int x) {
  int flag1 = (0x39 + (~x + 1)) >> 31;
  int flag2 = (x + (~0x30 + 1)) >> 31;
  return !(flag1 | flag2);
}
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
  int all1 = ~0;
  int flag = !(x^0);
  int result = ((flag + all1) & y) + ((!flag + all1) & z);
  return result;
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {

  int flag1 = (y >> 31)&1;
  int flag2 = (x >> 31)&1; 
  int sign = flag1 ^ flag2;  //x,y符号相同为0，不同为1
  int flag = ((y + (~x + 1)) >> 31) ; //x小于y为0，x大于y为1
  int result = (!sign & !flag) | (sign & flag2);
  return result;
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
 //超出要求操作数，可利用 x | ~x +1
int logicalNeg(int x) {

  int flag =   ((x>>31)&1)  +  ~0   ;      //x是正数，flag为全1，否则全0

  int result = (((0 + (~x + 1)) >> 31)& 1 & flag) + (((0 + x ) >>31 ) & 1  & (~flag));  //x非0为1，x为0为0

  return result ^ 1;
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
 //负数转化为正数处理不需要+1，因为有符号补码表示时，正数的范围总是比负数-1
int howManyBits(int x) {

  int x_sign = (x ^ (x >> 31)) ;  

  int b16_ = !!(x_sign>>16)<<4;
  int b08 = x_sign >> b16_;

  int b08_ = !!(b08>>8)<<3;
  int b04 = b08 >> b08_;

  int b04_ = !!(b04 >> 4)<<2;
  int b02 = b04 >> b04_;

  int b02_ = !!(b02 >> 2)<<1;
  int b01 = b02 >> b02_;

  int b01_ = !!(b01 >> 1);
  int b00 = b01 >> b01_;

  int result = b16_ + b08_ + b04_ + b02_ + b01_ + b00 + 1;
  return result;
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

  unsigned int sign  = uf  & 0x80000000;
  int exp = (uf >> 23) & 0xff;
  unsigned int frac = uf & 0x7fffff;
  int nan = !(exp ^ 0xff);
  int result;

  if(exp)
    exp = (exp + 1) << 23;
  else
  {
    exp = exp << 23;    //零值和此规格化值
      if(frac)
        frac = frac << 1;
  }

  result = sign | exp | frac;
  if(nan)
    result = uf;

  return result;
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

  int sign,exp,frac,frac_,result;
  int flag1,flag2,flag3;

  sign = uf & 0x80000000;
  exp = (uf >> 23) & 0xff;
  frac = uf & 0x7fffff;

  flag1 = exp + (~127 + 1);   //exp-127为负数取零
  flag2 = 157 + (~exp + 1) ;   //157-exp为负数则超范围
  flag3 = flag1 + (~23 + 1) ;  //超出尾数范围23左移，小于则右移

  if(flag1>>31)
    return 0;
  else
    if(flag2>>31)
      return 0x80000000u;
    else
    {
      frac_ = (1 << 23) | frac;   //最高位添加隐含的1
      if(flag3>>31)
        frac_ = frac_ >> (~flag3 + 1);
      else
        frac_ = frac_ << flag3;
    }

  if(sign)
    result = ~frac_ + 1 ;     //正数转化为负数（取反+1）
  else
    result = frac_;
  return result;
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

  int flag1,flag2,exp;

  flag1 = x + 126;
  flag2 = 127 + (~x + 1);   //

  if(flag1>>31)
    return 0;
  if(flag2>>31)
    return 0x7f800000;
  
  exp = x + 127;

    return exp << 23;
}
