#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#define ALG_REGULAR   22
#define ALG_OPTIMIZED 33

#ifndef OUTER_ITERATIONS
#error "Please define OUTER_ITERATIONS"
#endif

#ifndef INNER_ITERATIONS
#error "Please define INNER_ITERATIONS"
#endif

#if ALGORITHM == ALG_REGULAR
const char algorithm_string[] = "REGULAR";
unsigned int gcd(unsigned int int1, unsigned int int2) {
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
unsigned int gcd(unsigned int int1, unsigned int int2) {
   unsigned int temp;
 
   for (;;) {
      if ((temp = int1 % int2) == 0) {
         return(int2);
      }
      int1 = int2;
      int2 = temp;
   }
}

#else
#error "Please set ALGORITHM to ALG_REGULAR or ALG_OPTIMIZED"
#endif


static double timespec_to_secs(const struct timespec* spec) {
    return (double) spec->tv_sec + ((double) spec->tv_nsec / 1.0E+09);
}


int main(int argc, char* argv[]) {
    struct timespec start_time, stop_time;
    (void) argc;
    (void) argv;

    printf("Running %s algorithm. Outer iterations: %d, inner iterations: %d", algorithm_string, OUTER_ITERATIONS, INNER_ITERATIONS);

    (void) clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start_time);

    int i;
    for (i = 0; i < OUTER_ITERATIONS; ++i) {
        int r1 = rand();
        int r2 = rand();
        int j;
        for (j = 0; j < INNER_ITERATIONS; ++ j) {
            volatile unsigned int result = gcd(r1, r2);
            (void) result;
        }
    }

    (void) clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &stop_time);

    printf(", runtime: %0.3f.\n", timespec_to_secs(&stop_time) - timespec_to_secs(&start_time));

    return 0;
}
