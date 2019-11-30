#pragma GCC diagnostic ignored "-Wunused-variable"
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"

#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#define ALG_REGULAR     22
#define ALG_OPTIMIZED   33
#define ALG_OPTIMIZED2  44 

#define ARG_NOSWAP      99
#define ARG_BIGFIRST    100
#define ARG_SMALLFIRST  101

#ifndef OUTER_ITERATIONS
#error "Please define OUTER_ITERATIONS"
#endif

#ifndef INNER_ITERATIONS
#error "Please define INNER_ITERATIONS"
#endif

#ifndef INNER_ITERATIONS
#error "Please define INNER_ITERATIONS"
#endif

#if ALGORITHM == ALG_REGULAR
const char algorithm_string[] = "REGULAR";
unsigned int __attribute__ ((noinline))
gcd(unsigned int int1, unsigned int int2) {
   unsigned int temp;
 
   if (int1 < int2) {
      temp = int1;
      int1 = int2;
      int2 = temp;
   }

   for (;;) {
      if ((temp = int1 % int2) == 0) {
         return(int2);
      }
      int1 = int2;
      int2 = temp;
   }
}

#elif ALGORITHM == ALG_OPTIMIZED
const char algorithm_string[] = "OPTIMIZED";
unsigned int __attribute__ ((noinline))
gcd(unsigned int int1, unsigned int int2) {
   unsigned int temp;

   for (;;) {
      if ((temp = int1 % int2) == 0) {
         return(int2);
      }
      int1 = int2;
      int2 = temp;
   }
}

#elif ALGORITHM == ALG_OPTIMIZED2
const char algorithm_string[] = "OPTIMIZED2";
unsigned int __attribute__ ((noinline))
gcd(unsigned int int1, unsigned int int2) {
   unsigned int temp;

   while (int2 != 0) {
      temp = int2;
      int2 = int1 % int2;
      int1 = temp;
   }
   return int1;
}

#else
#error "Please set ALGORITHM to ALG_REGULAR or ALG_OPTIMIZED"
#endif

static double timespec_to_secs(const struct timespec* spec) {
    return (double) spec->tv_sec + ((double) spec->tv_nsec / 1.0E+09);
}

unsigned int __attribute__ ((noinline))
gcd_shell(unsigned int int1, unsigned int int2) {
    volatile unsigned int sint1 = int1;
    volatile unsigned int sint2 = int2;
    return 0;
}


double execute() {
    int i;
    struct timespec start_time, stop_time;

    (void) clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start_time);

    for (i = 0; i < OUTER_ITERATIONS; ++i) {
        int r1 = rand();
        int r2 = rand();
#if ARGUMENTS == ARG_BIGFIRST
        if (r1 < r2) {
            int temp = r1;
            r1 = r2;
            r2 = temp;
        }
#elif ARGUMENTS == ARG_SMALLFIRST
        if (r1 > r2) {
            int temp = r1;
            r1 = r2;
            r2 = temp;
        }
#elif ARGUMENTS == ARG_NOSWAP
        /* noop */
#else
#error "Please set ARGUMENTS to ARG_BIGFIRST, ARG_SMALLFIRST, or ARG_NOSWAP"
#endif
        int j;
        for (j = 0; j < INNER_ITERATIONS; ++ j) {
            volatile unsigned int result = gcd(r1, r2);
        }
    }

    (void) clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &stop_time);
    return timespec_to_secs(&stop_time) - timespec_to_secs(&start_time);
}

double execute_shell() {
    int i;
    struct timespec start_time, stop_time;

    (void) clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start_time);

    for (i = 0; i < OUTER_ITERATIONS; ++i) {
        int r1 = rand();
        int r2 = rand();
#if ARGUMENTS == ARG_BIGFIRST
        if (r1 < r2) {
            int temp = r1;
            r1 = r2;
            r2 = temp;
        }
#elif ARGUMENTS == ARG_SMALLFIRST
        if (r1 > r2) {
            int temp = r1;
            r1 = r2;
            r2 = temp;
        }
#elif ARGUMENTS == ARG_NOSWAP
        /* noop */
#else
#error "Please set ARGUMENTS to ARG_BIGFIRST, ARG_SMALLFIRST, or ARG_NOSWAP"
#endif
        volatile unsigned int result2 = gcd_shell(r1, r2);
    }

    (void) clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &stop_time);
    return timespec_to_secs(&stop_time) - timespec_to_secs(&start_time);
}

int main(int argc, char* argv[]) {
    (void) argc;
    (void) argv;

    double runtime = execute();
    double overhead = execute_shell();

    printf("Running %s algorithm. Outer iterations: %d, inner iterations: %d", algorithm_string, OUTER_ITERATIONS, INNER_ITERATIONS);
    printf(", runtime: %0.3f, overhead: %0.12f.\n", runtime - overhead, overhead);

    return 0;
}
