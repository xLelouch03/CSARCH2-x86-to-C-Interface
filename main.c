#include <stdio.h>
#include <stdlib.h>
#include <time.h>

extern void x8664(int n, float* arr1, float* arr2, float* sdot);

void dotprod(int n, float* arr1, float* arr2, float* sdot) {
    int i;
    *sdot = 0.0;

    for (i = 0; i < n; i++) {
        *sdot += (arr1[i] * arr2[i]);
    }
}

int main() {

    const int N = 1 << 24;
    const int ARRAY_BYTES = N * sizeof(int);
    printf("Array size: %d\n", N);

    //timer variable
    clock_t begin, end;
    double time_taken;
    double avg_time;

    float* array1;
    float* array2;
    float sdot1;
    float sdot2;
    double c_time;
    double asm_time;
    array1 = (float*)malloc(N * sizeof(float));
    array2 = (float*)malloc(N * sizeof(float));

    if (array1 == NULL || array2 == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    };

    int i;

    for (i = 0; i < N; i++) {
        array1[i] = 0.000000312f;
        array2[i] = 0.0000003455f;
    }

    // fill the cache
    dotprod(N, array1, array2, &sdot1);

    int loop = 30;
    begin = clock();
    for (int j = 0; j < loop; j++) {
        dotprod(N, array1, array2, &sdot1);
        printf("Dot Product is %.10f\n", sdot1);
    }
    end = clock();

    time_taken = ((double)(end - begin)) * 1e3 / CLOCKS_PER_SEC;
    avg_time = time_taken / loop;

    c_time = avg_time;

    printf("C function takes %lf milliseconds for array size %d\n", time_taken, N);
    printf("Average Execution time: %lf with loop count: %d\n", avg_time, loop);
    printf("\n");

    //fill the cache
    x8664(N, array1, array2, &sdot2);
    begin = clock();
    for (int j = 0; j < loop; j++) {
       x8664(N, array1, array2, &sdot2);
       printf("Dot Product is %.10f\n", sdot2);
    }
    end = clock();

    time_taken = ((double)(end - begin)) * 1e3 / CLOCKS_PER_SEC;
    avg_time = time_taken / loop;

    asm_time = avg_time;

    printf("Assembly function takes %lf milliseconds for array size %d\n", time_taken, N);
    printf("Average Execution time: %lf with loop count: %d\n\n", avg_time, loop);

    //compare both times
    printf("C function takes %lfx ms more than Assembly\n\n", c_time / asm_time);
    printf("ASM function takes %lfx ms more than C\n", asm_time / c_time);

    free(array1);
    free(array2);

    return 0;
}
