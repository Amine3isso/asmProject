section .text
global reverse_array_asm
global find_second_largest_asm

; Reverse an array of 32-bit integers
; Input: RDI (array pointer), RSI (number of elements)
reverse_array_asm:
    test rsi, rsi
    jz .done              ; Early return if length = 0
    
    cmp rsi, 1
    je .done              ; Nothing to do for single element
    
    mov rax, rdi           ; start pointer
    lea rdx, [rdi + rsi*4 - 4] ; end pointer
    
.loop:
    cmp rax, rdx
    jge .done
    
    mov ecx, [rax]         ; swap elements
    mov r8d, [rdx]
    mov [rdx], ecx
    mov [rax], r8d
    
    add rax, 4
    sub rdx, 4
    jmp .loop
    
.done:
    ret

; Find second largest element in array
; Input: RDI (array pointer), RSI (number of elements)
; Output: EAX (second largest, -1 if invalid)
find_second_largest_asm:
    cmp rsi, 2
    jl .error              ; need at least 2 elements
    
    mov eax, [rdi]         ; largest = first element
    mov edx, [rdi + 4]     ; second = second element
    
    cmp eax, edx
    jge .init_ok
    xchg eax, edx          ; ensure eax >= edx
    
.init_ok:
    mov rcx, 2             ; start from third element
    
.loop:
    cmp rcx, rsi
    jge .done
    
    mov r8d, [rdi + rcx*4]
    cmp r8d, eax
    jle .not_larger
    
    mov edx, eax           ; new second = old largest
    mov eax, r8d           ; new largest = current
    jmp .next
    
.not_larger:
    cmp r8d, edx
    jle .next
    mov edx, r8d           ; new second = current
    
.next:
    inc rcx
    jmp .loop
    
.error:
    mov eax, -1            ; error code
    ret
    
.done:
    mov eax, edx           ; return second largest
    ret