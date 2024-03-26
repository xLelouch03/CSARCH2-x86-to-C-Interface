# LBYARCH x86 to C Interface Programming Project

## Specification:
Write the kernel in (1) C program and (2) an x86-64 assembly language. The kernel is to perform a dot product between vector A and vector B and place the result in sdot.
- Required to use functional scalar SIMD registers
- Required to use functional scalar SIMD floating-point instructions
Input: Scalar variable n (integer) contains the length of the vector; Vectors A and B are both single-precision float. Scalar sdot is a single-precision float.

Process: $$sdot = \sum_{i=1}^n a_i b_i = a_1 b_1 + a_2 b_2 + a_n b_n$$
Output: store the result in memory location sdot. Display the result for all versions of the kernel (i.e., C and x86-64).
