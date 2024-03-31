# LBYARCH x86 to C Interface Programming Project

## Specification:
Write the kernel in (1) C program and (2) an x86-64 assembly language. The kernel is to perform a dot product between vector A and vector B and place the result in sdot.
- Required to use functional scalar SIMD registers
- Required to use functional scalar SIMD floating-point instructions
Input: Scalar variable n (integer) contains the length of the vector; Vectors A and B are both single-precision floats. Scalar sdot is a single-precision float.

Process: $$sdot = \sum_{i=1}^n a_i b_i = a_1 b_1 + a_2 b_2 + ... + a_n b_n$$
Output: store the result in memory location sdot. Display the result for all versions of the kernel (i.e., C and x86-64).

## To run

1. Clone the repo
2. Open the .sln file in Visual Studio
3. Run the code with the appropriate mode (debug/release)
4. Enter your desired array size (limited to 2^x)
5. Wait for the code to finish running

## Comparison and Analysis of Execution times

### Debug Mode
In debug mode, C performs at least 3x slower than ASM in all the specified array sizes. This is because debug mode in C has optimizations off and has debug features turned on, which are extra overhead. On the other hand, as ASM is a low-level language, there are no extra features with overhead, and all optimizations are done in the code itself instead of during compilation. 

| Debug Mode | $2^{20}$ | $2^{24}$ | $2^{30}$ |
| --- | --- | --- | --- |
| C | 1.9333 | 33.0333 | 2062.6333 |
| ASM | 0.5 | 9.8333 | 619.9667 |
| C is slower than ASM by | 3.867x | 3.359x | 3.327x |

### Release Mode
For release mode, C has its speed optimizations on, and the debug features, which cost extra overhead, are off. This allows release mode C to pull ahead of ASM in terms of speed. In addition, the ASM code may still have room for optimizations, which may contribute to its slower speed compared to release mode C.

| Release Mode | $2^{20}$ | $2^{24}$ | $2^{30}$ |
| --- | --- | --- | --- |
| C | 0.5 | 9.633 | 604.633 |
| ASM | 0.533 | 9.8 | 622.667 |
| ASM is slower than C by | 1.067x | 1.017x | 1.03x |

### Optimizations
As the project specifications asked for correctness checking, we needed to store the dot product results of every loop to make sure that every run resulted in the same answer. Since the dotproduct function in C accesses the pointer to the array element directly $2^{n+1}$ times, this slowed down the code in C. To address this, a temporary variable was used instead to hold the sdot result so that the pointer would only be used once during the function's lifetime. This change allowed the release mode C to be faster than the ASM code.

## Screenshots with Correctness Checking
To check for the correctness in C, we checked that the output for all the runs of the C kernel resulted in the same output. Do note that this checking is done after the C kernel is run and the timer stopped.

To check for the correctness in ASM, we checked that each of the outputs in the runs of the ASM kernel resulted in the same output for the corresponding C kernel run (run #10 output of ASM will be compared with run #10 output of C).

Note that for these screenshots, the output being shown is the output of the first run for each kernel. Additionally, for error checking, any errors found will be printed into the console.

### Debug Mode Outputs

#### $2^{20}$
![2^20 Debug Mode output](/imgs/2^20_DebugMode.png)

#### $2^{24}$
![2^24 Debug Mode output](/imgs/2^24_DebugMode.png)

#### $2^{30}$
![2^30 Debug Mode output](/imgs/2^30_DebugMode.png)

### Release Mode Outputs

#### $2^{20}$
![2^20 Release Mode output](/imgs/2^20_ReleaseMode.png)

#### $2^{24}$
![2^24 Release Mode output](/imgs/2^24_ReleaseMode.png)

#### $2^{30}$
![2^30 Release Mode output](/imgs/2^30_ReleaseMode.png)
