#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "asm_functions.h"

void test_strlen() {
    const char* test_cases[] = {
        "",
        "a",
        "hello",
        "long string with spaces",
        NULL
    };
    
    size_t expected[] = {
        0,
        1,
        5,
        20
    };
    
    printf("Testing strlen_asm:\n");
    for (int i = 0; test_cases[i] != NULL; i++) {
        size_t asm_len = strlen_asm(test_cases[i]);
        size_t c_len = strlen(test_cases[i]);
        
        printf("  '%s' - C: %zu, ASM: %zu - ", 
               test_cases[i], c_len, asm_len);
        
        assert(asm_len == c_len);
        assert(asm_len == expected[i]);
        printf("OK\n");
    }
}

void test_strrev() {
    struct TestCase {
        char input[50];
        char expected[50];
    } test_cases[] = {
        {"", ""},
        {"a", "a"},
        {"ab", "ba"},
        {"abc", "cba"},
        {"hello", "olleh"},
        {"racecar", "racecar"},
        {"12345", "54321"}
    };
    
    printf("\nTesting strrev_asm:\n");
    for (size_t i = 0; i < sizeof(test_cases)/sizeof(test_cases[0]); i++) {
        char buffer[50];
        strcpy(buffer, test_cases[i].input);
        
        strrev_asm(buffer);
        
        printf("  '%s' -> '%s' (expected '%s') - ",
               test_cases[i].input, buffer, test_cases[i].expected);
        
        assert(strcmp(buffer, test_cases[i].expected) == 0);
        printf("OK\n");
    }
}

int main() {
    test_strlen();
    test_strrev();
    printf("\nAll string tests passed!\n");
    return 0;
}