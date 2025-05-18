section .text
global reverse_number_asm

; Reverse digits of a 32-bit integer
; Input: EDI (number to reverse)
; Output: EAX (reversed number)
reverse_number_asm:
    xor eax, eax            ; EAX will store the reversed number
    mov ecx, 10             ; divisor
    mov ebx, edi            ; original number
    
.loop:
    xor edx, edx
    mov eax, ebx
    div ecx                 ; EDX = remainder (last digit)
    
    imul eax, eax, 10       ; reversed = reversed * 10
    add eax, edx            ; reversed += digit
    
    mov ebx, [esp + 4]      ; reload original number
    test ebx, ebx
    jnz .loop
    
    ret