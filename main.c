//
//  main.c
//  fpu
//
//  Created by Adolfo Eloy on 01/04/18.
//
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <pthread.h>

#define NTHREADS 100
#define MAX 10000

typedef struct Thread {
    long start;
    long end;
} Thread_t;

void* inner_function(void* params);

int main() {
    long range = MAX / NTHREADS;
    srand(time(0));

    pthread_t threads[NTHREADS];
    long offset = 0;
    for (long j=0; j < NTHREADS; j++) {
        Thread_t* thread_range = malloc(sizeof(Thread_t));
        thread_range->start = j + offset;
        thread_range->end = j + offset + range;
        offset += range - 1;

        pthread_create(&threads[j], NULL, inner_function, (void*) thread_range);
    }

    double result = 0;
    for (long j=0; j < NTHREADS; j++) {
      void* tmp_result;
      pthread_join(threads[j], &tmp_result);
      result += (*(double*)tmp_result);
    }

    printf("finished - result: %lf\n", result);
    exit(0);
}

void* inner_function(void* params) {
    double s, D;
    Thread_t* thread_range = (Thread_t*) params;
    double* result = malloc(sizeof(double));
    *result = 1;

    for (long j = thread_range->start; j < thread_range->end; j++) {
        s = (rand() % 1000);
        for (long i = 0; i < MAX; i++) {
            D = pow((rand() % 100), (rand() % 1000));
            (*result) += 1/(pow(s, D));
        }
    }

    return (void*)result;
}
