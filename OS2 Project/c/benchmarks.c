#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "asm_functions.h"

#define ITERATIONS 10000000
#define ARRAY_SIZE 1000

// C implementations for comparison
int reverse_number_c(int num) {
    int reversed = 0;
    while (num != 0) {
        reversed = reversed * 10 + num % 10;
        num /= 10;
    }
    return reversed;
}

size_t strlen_c(const char *str) {
    size_t len = 0;
    while (*str++) len++;
    return len;
}

void strrev_c(char *str) {
    char *end = str + strlen_c(str) - 1;
    while (str < end) {
        char tmp = *str;
        *str++ = *end;
        *end-- = tmp;
    }
}

void reverse_array_c(int *arr, size_t len) {
    for (size_t i = 0; i < len/2; i++) {
        int tmp = arr[i];
        arr[i] = arr[len-1-i];
        arr[len-1-i] = tmp;
    }
}

int find_second_largest_c(int *arr, size_t len) {
    if (len < 2) return -1;
    
    int first = arr[0], second = arr[1];
    if (first < second) {
        int tmp = first;
        first = second;
        second = tmp;
    }
    
    for (size_t i = 2; i < len; i++) {
        if (arr[i] > first) {
            second = first;
            first = arr[i];
        } else if (arr[i] > second) {
            second = arr[i];
        }
    }
    return second;
}

// Benchmarking infrastructure
void run_benchmark(const char *name, void (*asm_func)(void), void (*c_func)(void)) {
    struct timespec start, end;
    long asm_ns, c_ns;
    
    // Benchmark ASM
    clock_gettime(CLOCK_MONOTONIC, &start);
    asm_func();
    clock_gettime(CLOCK_MONOTONIC, &end);
    asm_ns = (end.tv_sec - start.tv_sec) * 1000000000 + (end.tv_nsec - start.tv_nsec);
    
    // Benchmark C
    clock_gettime(CLOCK_MONOTONIC, &start);
    c_func();
    clock_gettime(CLOCK_MONOTONIC, &end);
    c_ns = (end.tv_sec - start.tv_sec) * 1000000000 + (end.tv_nsec - start.tv_nsec);
    
    // Results
    printf("%-20s ASM: %8ld ns | C: %8ld ns | Difference: %6.2f%% (%s)\n",
           name, asm_ns, c_ns,
           100.0 * (asm_ns - c_ns) / c_ns,
           asm_ns < c_ns ? "FASTER" : "slower");
}

// Benchmark test cases
void benchmark_reverse_number() {
    int num = 123456789;
    int result_asm, result_c;
    
    void asm_test() {
        for (int i = 0; i < ITERATIONS; i++) {
            result_asm = reverse_number_asm(num);
        }
    }
    
    void c_test() {
        for (int i = 0; i < ITERATIONS; i++) {
            result_c = reverse_number_c(num);
        }
    }
    
    run_benchmark("reverse_number", asm_test, c_test);
}

void benchmark_strlen() {
    char *str = "This is a test string for benchmarking";
    size_t result_asm, result_c;
    
    void asm_test() {
        for (int i = 0; i < ITERATIONS; i++) {
            result_asm = strlen_asm(str);
        }
    }
    
    void c_test() {
        for (int i = 0; i < ITERATIONS; i++) {
            result_c = strlen_c(str);
        }
    }
    
    run_benchmark("strlen", asm_test, c_test);
}

void benchmark_strrev() {
    char str_asm[50] = "A string to reverse";
    char str_c[50] = "A string to reverse";
    
    void asm_test() {
        for (int i = 0; i < ITERATIONS/10; i++) {
            strcpy(str_asm, "A string to reverse");
            strrev_asm(str_asm);
        }
    }
    
    void c_test() {
        for (int i = 0; i < ITERATIONS/10; i++) {
            strcpy(str_c, "A string to reverse");
            strrev_c(str_c);
        }
    }
    
    run_benchmark("strrev", asm_test, c_test);
}

void benchmark_reverse_array() {
    int *arr_asm = malloc(ARRAY_SIZE * sizeof(int));
    int *arr_c = malloc(ARRAY_SIZE * sizeof(int));
    
    // Initialize array
    for (int i = 0; i < ARRAY_SIZE; i++) {
        arr_asm[i] = arr_c[i] = i;
    }
    
    void asm_test() {
        for (int i = 0; i < ITERATIONS/100; i++) {
            reverse_array_asm(arr_asm, ARRAY_SIZE);
        }
    }
    
    void c_test() {
        for (int i = 0; i < ITERATIONS/100; i++) {
            reverse_array_c(arr_c, ARRAY_SIZE);
        }
    }
    
    run_benchmark("reverse_array", asm_test, c_test);
    free(arr_asm);
    free(arr_c);
}

void benchmark_second_largest() {
    int *arr_asm = malloc(ARRAY_SIZE * sizeof(int));
    int *arr_c = malloc(ARRAY_SIZE * sizeof(int));
    int result_asm, result_c;
    
    // Initialize array with random values
    srand(time(NULL));
    for (int i = 0; i < ARRAY_SIZE; i++) {
        arr_asm[i] = arr_c[i] = rand() % 1000;
    }
    
    void asm_test() {
        for (int i = 0; i < ITERATIONS/10; i++) {
            result_asm = find_second_largest_asm(arr_asm, ARRAY_SIZE);
        }
    }
    
    void c_test() {
        for (int i = 0; i < ITERATIONS/10; i++) {
            result_c = find_second_largest_c(arr_c, ARRAY_SIZE);
        }
    }
    
    run_benchmark("second_largest", asm_test, c_test);
    free(arr_asm);
    free(arr_c);
}

int main() {
    printf("\nBenchmark Results (Iterations: %d, Array Size: %d)\n", ITERATIONS, ARRAY_SIZE);
    printf("------------------------------------------------\n");
    
    benchmark_reverse_number();
    benchmark_strlen();
    benchmark_strrev();
    benchmark_reverse_array();
    benchmark_second_largest();
    
    printf("\nNote:\n");
    printf("- Times are total nanoseconds for all iterations\n");
    printf("- strrev and array operations use fewer iterations due to higher overhead\n");
    printf("- Positive percentage means assembly is slower, negative means faster\n");
    
    return 0;
}