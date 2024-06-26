#include <stdio.h>
#include <stdlib.h>
#include <time.h>

extern void x8664(int n, float* arr1, float* arr2, float* sdot);

void dotprod(int n, float* arr1, float* arr2, float* sdot) {
    int i;
    float ans = 0.0;

    for (i = 0; i < n; i++) {
        ans = ans + (arr1[i] * arr2[i]);
    }

    *sdot = ans;
}

int main() {
    printf("\nArray size: 2^");
    int input;
    scanf_s("%d", &input);
    const int N = 1 << input;
    printf("Array size: %d\n", N);
    const int ARRAY_BYTES = N * sizeof(int);


    //timer variable
    clock_t begin, end;
    double time_taken;
    double avg_time;

    float* array1;
    float* array2;
    float* sdot1;
    float* sdot2;
    double c_time[2];
    double asm_time[2];
    int loop = 30;
    int errCount_C = 0;
    int errCount_ASM = 0;

    array1 = (float*)malloc(N * sizeof(float));
    array2 = (float*)malloc(N * sizeof(float));
    sdot1 = (float*)malloc(loop * sizeof(float));
    sdot2 = (float*)malloc(loop * sizeof(float));

    if (array1 == NULL || array2 == NULL || sdot1 == NULL || sdot2 == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    };

    int i;

    for (i = 0; i < N; i++) {
        array1[i] = 0.000000312f;
        array2[i] = 0.0000003455f;
    }

    printf("---------- C Function ----------\n\n");

    // fill the cache
    dotprod(N, array1, array2, &sdot1[0]);


    begin = clock();
    for (int j = 0; j < loop; j++) {
        dotprod(N, array1, array2, &sdot1[j]);
    }
    end = clock();

    // Correctness check
    for (int j = 0; j < loop - 1; j++) {
        if (sdot1[j] != sdot1[j + 1]) {
            printf("Error: C function has multiple results\n");
            printf("Result 1: %.10f\n", sdot1[j]);
            printf("Result 2: %.10f\n", sdot1[j + 1]);
            errCount_C++;
        };
    }
    if (errCount_C == 0) {
        printf("C function exhibits no errors (All results are the same)\n");
    } else {
        printf("C function has %d errors\n", errCount_C);
    }


    printf("Dot Product is %.10f\n", sdot1[0]);

    time_taken = ((double)(end - begin)) * 1e3 / CLOCKS_PER_SEC;
    avg_time = time_taken / loop;

    c_time[0] = avg_time;
    c_time[1] = time_taken;

    printf("\n\n---------- Assembly Function ----------\n\n");

    //fill the cache
    x8664(N, array1, array2, &sdot2[0]);

    begin = clock();
    for (int j = 0; j < loop; j++) {
        x8664(N, array1, array2, &sdot2[j]);
    }
    end = clock();

    // Correctness check
    for (int j = 0; j < loop; j++) {
        if (sdot1[j] != sdot2[j]) {
            printf("Error: C and Assembly function results are not same\n");
            printf("C: %.10f\n", sdot1[j]);
            printf("Assembly: %.10f\n", sdot2[j]);
            errCount_ASM++;
        }
    }
    
    if (errCount_ASM == 0) {
        printf("Assembly function exhibits no errors (Result is the same with C output)\n");
    } else {
        printf("Assembly function has %d errors\n", errCount_ASM);
    }

    printf("Dot Product is %.10f\n", sdot2[0]);
    
    time_taken = ((double)(end - begin)) * 1e3 / CLOCKS_PER_SEC;
    avg_time = time_taken / loop;

    asm_time[0] = avg_time;
    asm_time[1] = time_taken;


    printf("\n-------------Time Comparison-------------\n\n");
    printf("C function takes %lf milliseconds for array size %d\n", c_time[1], N);
    printf("Average Execution time: %lf with loop count: %d\n", c_time[0], loop);
    printf("\n");

    printf("Assembly function takes %lf milliseconds for array size %d\n", asm_time[1], N);
    printf("Average Execution time: %lf with loop count: %d\n\n", asm_time[0], loop);

    //compare both times
    printf("C function is %lfx slower than Assembly\n\n", c_time[0] / asm_time[0]);
    printf("ASM function is %lfx slower than C\n", asm_time[0] / c_time[0]);

    free(array1);
    free(array2);
    free(sdot1);
    free(sdot2);

    return 0;
}
