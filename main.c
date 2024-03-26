#include <stdio.h>
#include <stdlib.h>
#include <time.h>

extern void x8664();

void dotprod(int n, float* arr1, float* arr2, float* sdot) {
    int i;
    *sdot = 0.0;

    for (i = 0; i < n; i++) {
        *sdot = *sdot + (arr1[i] * arr2[i]);
    }
    printf("Dot Product is %.2f\n", *sdot);
}

int main() {

    const int N = 1 << 28;
    const int ARRAY_BYTES = N * sizeof(int);

    //timer variable
    clock_t begin, end;
    double time_taken;
    double avg_time;

    float* array1;
    float* array2;
    float sdot;
    array1 = (float*)malloc(N * sizeof(float));
    array2 = (float*)malloc(N * sizeof(float));

    int i;

    for (i = 0; i < N; i++) {
        array1[i] = 1.0;
        array2[i] = 1.0;
    }
    // fill the cache
    dotprod(N, array1, array2, &sdot);

    int loop = 30;
    begin = clock();
    for (int j = 0; j < loop; j++) {
        dotprod(N, array1, array2, &sdot);
    }
    end = clock();
    //avg_time = elapse / loop
    time_taken = ((double)(end - begin)) * 1e3 / CLOCKS_PER_SEC;
    avg_time = time_taken / loop;
    printf("C function takes %lf milliseconds for array size %d\n", time_taken, N);
    printf("Average Execution time: %lf with loop count: %d\n",avg_time, loop);

    free(array1);
    free(array2);

    return 0;
}
