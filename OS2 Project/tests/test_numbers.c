#include <stdio.h>
#include <assert.h>
#include "asm_functions.h"

void test_reverse_number() {
    assert(reverse_number_asm(12345) == 54321);
    assert(reverse_number_asm(100) == 1);
    assert(reverse_number_asm(0) == 0);
    assert(reverse_number_asm(5) == 5);
    printf("Number tests passed!\n");
}

int main() {
    test_reverse_number();
    return 0;
}