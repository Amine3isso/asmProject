#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "asm_functions.h"

// Function prototypes for C implementations
int reverse_number_c(int num);
size_t strlen_c(const char *str);
void strrev_c(char *str);
void reverse_array_c(int *arr, size_t len);
int find_second_largest_c(int *arr, size_t len);

void print_array(int *arr, size_t len) {
    printf("[");
    for (size_t i = 0; i < len; i++) {
        printf("%d", arr[i]);
        if (i < len - 1) printf(", ");
    }
    printf("]");
}

void demo_reverse_number() {
    printf("\n=== Number Reversal Demo ===\n");
    
    int numbers[] = {0, 5, 123, 100, 123456789, -12345};
    size_t count = sizeof(numbers)/sizeof(numbers[0]);
    
    for (size_t i = 0; i < count; i++) {
        int num = numbers[i];
        int asm_result = reverse_number_asm(num);
        int c_result = reverse_number_c(num);
        
        printf("Input: %10d | ASM: %10d | C: %10d | %s\n",
               num, asm_result, c_result,
               asm_result == c_result ? "✓" : "✗");
    }
}

void demo_strlen() {
    printf("\n=== String Length Demo ===\n");
    
    const char *strings[] = {
        "",
        "a",
        "hello",
        "longer string with spaces",
        NULL
    };
    
    for (int i = 0; strings[i] != NULL; i++) {
        size_t asm_len = strlen_asm(strings[i]);
        size_t c_len = strlen_c(strings[i]);
        
        printf("Input: '%s'\n", strings[i]);
        printf("  ASM length: %2zu | C length: %2zu | %s\n",
               asm_len, c_len,
               asm_len == c_len ? "✓" : "✗");
    }
}

void demo_strrev() {
    printf("\n=== String Reversal Demo ===\n");
    
    char strings[][50] = {
        "",
        "a",
        "ab",
        "abc",
        "hello",
        "racecar",
        "12345"
    };
    size_t count = sizeof(strings)/sizeof(strings[0]);
    
    for (size_t i = 0; i < count; i++) {
        char asm_str[50], c_str[50];
        strcpy(asm_str, strings[i]);
        strcpy(c_str, strings[i]);
        
        strrev_asm(asm_str);
        strrev_c(c_str);
        
        printf("Original: '%s'\n", strings[i]);
        printf("  ASM reversed: '%s' | C reversed: '%s' | %s\n",
               asm_str, c_str,
               strcmp(asm_str, c_str) == 0 ? "✓" : "✗");
    }
}

void demo_array_reversal() {
    printf("\n=== Array Reversal Demo ===\n");
    
    int test_arrays[][5] = {
        {0},                     // Empty array
        {1},                    // Single element
        {1, 2},                 // Two elements
        {1, 2, 3},              // Odd length
        {1, 2, 3, 4},           // Even length
        {5, 2, 9, 1, 7}         // Mixed values
    };
    size_t lengths[] = {0, 1, 2, 3, 4, 5};
    size_t count = sizeof(lengths)/sizeof(lengths[0]);
    
    for (size_t i = 0; i < count; i++) {
        size_t len = lengths[i];
        int *asm_arr = malloc(len * sizeof(int));
        int *c_arr = malloc(len * sizeof(int));
        
        if (len > 0) {
            memcpy(asm_arr, test_arrays[i], len * sizeof(int));
            memcpy(c_arr, test_arrays[i], len * sizeof(int));
        }
        
        reverse_array_asm(asm_arr, len);
        reverse_array_c(c_arr, len);
        
        printf("Original: ");
        if (len > 0) print_array(test_arrays[i], len);
        else printf("[]");
        
        printf("\n  ASM reversed: ");
        if (len > 0) print_array(asm_arr, len);
        else printf("[]");
        
        printf("\n  C reversed:   ");
        if (len > 0) print_array(c_arr, len);
        else printf("[]");
        
        int match = (len == 0) || 
                   (memcmp(asm_arr, c_arr, len * sizeof(int)) == 0);
        printf("\n  %s\n\n", match ? "✓" : "✗");
        
        free(asm_arr);
        free(c_arr);
    }
}

void demo_second_largest() {
    printf("\n=== Second Largest Element Demo ===\n");
    
    struct TestCase {
        int array[5];
        size_t len;
        int expected;
    } test_cases[] = {
        {{1, 2}, 2, 1},               // Simple case
        {{5, 2, 9, 1, 7}, 5, 7},      // Typical case
        {{9, 9, 8, 8}, 4, 9},         // Duplicates
        {{-5, -2, -9}, 3, -5},        // Negative numbers
        {{1, 1, 1, 1}, 4, -1},        // All same (invalid)
        {{1}, 1, -1}                  // Single element (invalid)
    };
    size_t count = sizeof(test_cases)/sizeof(test_cases[0]);
    
    for (size_t i = 0; i < count; i++) {
        int asm_result = find_second_largest_asm(test_cases[i].array, test_cases[i].len);
        int c_result = find_second_largest_c(test_cases[i].array, test_cases[i].len);
        
        printf("Array: ");
        print_array(test_cases[i].array, test_cases[i].len);
        printf("\n  ASM result: %2d | C result: %2d | Expected: %2d | %s\n",
               asm_result, c_result, test_cases[i].expected,
               (asm_result == c_result && asm_result == test_cases[i].expected) ? "✓" : "✗");
    }
}

int main() {
    printf("===== Assembly Function Demonstrations =====\n");
    
    demo_reverse_number();
    demo_strlen();
    demo_strrev();
    demo_array_reversal();
    demo_second_largest();
    
    printf("\nNote:\n");
    printf("✓ indicates ASM and C implementations agree\n");
    printf("✗ indicates a discrepancy between implementations\n");
    
    return 0;
}

// C implementations for verification
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