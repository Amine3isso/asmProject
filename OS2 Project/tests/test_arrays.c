#include <stdio.h>
#include <assert.h>
#include "asm_functions.h"

void print_array(int *arr, size_t len) {
    printf("[");
    for (size_t i = 0; i < len; i++) {
        printf("%d", arr[i]);
        if (i < len - 1) printf(", ");
    }
    printf("]");
}

void test_reverse_array() {
    struct TestCase {
        int input[10];
        int expected[10];
        size_t len;
    } test_cases[] = {
        {{0}, {0}, 0},                   // empty array
        {{1}, {1}, 1},                 // single element
        {{1, 2}, {2, 1}, 2},           // two elements
        {{1, 2, 3}, {3, 2, 1}, 3},     // odd length
        {{1, 2, 3, 4}, {4, 3, 2, 1}, 4}, // even length
        {{5, 2, 9, 1, 7}, {7, 1, 9, 2, 5}, 5} // mixed values
    };
    
    printf("Testing reverse_array_asm:\n");
    for (size_t i = 0; i < sizeof(test_cases)/sizeof(test_cases[0]); i++) {
        int arr[10];
        memcpy(arr, test_cases[i].input, test_cases[i].len * sizeof(int));
        
        reverse_array_asm(arr, test_cases[i].len);
        
        printf("  Input: ");
        print_array(test_cases[i].input, test_cases[i].len);
        printf(" -> ");
        print_array(arr, test_cases[i].len);
        printf(" - ");
        
        assert(memcmp(arr, test_cases[i].expected, 
               test_cases[i].len * sizeof(int)) == 0);
        printf("OK\n");
    }
}

void test_find_second_largest() {
    struct TestCase {
        int input[10];
        size_t len;
        int expected;
    } test_cases[] = {
        {{1, 2}, 2, 1},               // simple case
        {{5, 2, 9, 1, 7}, 5, 7},      // typical case
        {{9, 9, 8, 8}, 4, 9},         // duplicates
        {{-5, -2, -9}, 3, -5},        // negative numbers
        {{1, 1, 1, 1}, 4, -1},        // all same (invalid)
        {{1}, 1, -1}                  // single element (invalid)
    };
    
    printf("\nTesting find_second_largest_asm:\n");
    for (size_t i = 0; i < sizeof(test_cases)/sizeof(test_cases[0]); i++) {
        int result = find_second_largest_asm(test_cases[i].input, test_cases[i].len);
        
        printf("  Input: ");
        print_array(test_cases[i].input, test_cases[i].len);
        printf(" -> %d (expected %d) - ", result, test_cases[i].expected);
        
        assert(result == test_cases[i].expected);
        printf("OK\n");
    }
}

int main() {
    test_reverse_array();
    test_find_second_largest();
    printf("\nAll array tests passed!\n");
    return 0;
}