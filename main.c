#include <stdio.h>
#include <stdlib.h>
#include <time.h>

extern void x8664(int n, float* arr1, float* arr2, float* sdot);

void dotprod(int n, float* arr1, float* arr2, float* sdot) {
    int i;
    *sdot = 0.0;

    for (i = 0; i < n; i++) {
        *sdot = *sdot + (arr1[i] * arr2[i]);
    }
}

int main() {

    const int N = 1 << 20;
    const int ARRAY_BYTES = N * sizeof(int);

    //timer variable
    clock_t begin, end;
    double time_taken;
    double avg_time;

    float* array1;
    float* array2;
    float sdot1;
    float sdot2;
    array1 = (float*)malloc(N * sizeof(float));
    array2 = (float*)malloc(N * sizeof(float));

    int i;

    for (i = 0; i < N; i++) {
        array1[i] = 10.0;
        array2[i] = 10.0;
    }
    // fill the cache
    dotprod(N, array1, array2, &sdot1);

    int loop = 30;
    begin = clock();
    for (int j = 0; j < loop; j++) {
        dotprod(N, array1, array2, &sdot1);
        printf("Dot Product is %.2f\n", sdot1);
    }
    end = clock();
    time_taken = ((double)(end - begin)) * 1e3 / CLOCKS_PER_SEC;
    avg_time = time_taken / loop;
    printf("C function takes %lf milliseconds for array size %d\n", time_taken, N);
    printf("Average Execution time: %lf with loop count: %d\n", avg_time, loop);
    printf("\n");

    //fill the cache
    //x8664(N, array1, array2, &sdot2);
    begin = clock();
    for (int j = 0; j < loop; j++) {
       x8664(N, array1, array2, &sdot2);
       printf("Dot Product is %.2f\n", sdot2);
    }
    end = clock();

    time_taken = ((double)(end - begin)) * 1e3 / CLOCKS_PER_SEC;
    avg_time = time_taken / loop;
    printf("Assembly function takes %lf milliseconds for array size %d\n", time_taken, N);
    printf("Average Execution time: %lf with loop count: %d\n", avg_time, loop);

    free(array1);
    free(array2);

    return 0;
}
