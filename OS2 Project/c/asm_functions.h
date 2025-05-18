#ifndef ASM_FUNCTIONS_H
#define ASM_FUNCTIONS_H

#include <stddef.h>

// Numbers
int reverse_number_asm(int num);

// Strings
size_t strlen_asm(const char *str);
void strrev_asm(char *str);

// Arrays
void reverse_array_asm(int *arr, size_t len);
int find_second_largest_asm(int *arr, size_t len);

#endif