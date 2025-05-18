section .text
global strlen_asm

; Calculate length of null-terminated string
; Input: RDI (string pointer)
; Output: RAX (string length)
strlen_asm:
    xor rax, rax            ; RAX will hold length
    
.loop:
    cmp byte [rdi + rax], 0
    je .done
    inc rax
    jmp .loop
    
.done:
    ret

global strrev_asm

; Reverse a string in place
; Input: RDI (string pointer)
strrev_asm:
    call strlen_asm         ; get length in RAX
    cmp rax, 1
    jle .done              ; nothing to do for empty or single-char strings
    
    mov rsi, rdi           ; start pointer
    lea rdi, [rdi + rax - 1] ; end pointer
    
.loop:
    cmp rsi, rdi
    jge .done
    
    mov al, [rsi]
    mov ah, [rdi]
    mov [rdi], al
    mov [rsi], ah
    
    inc rsi
    dec rdi
    jmp .loop
    
.done:
    ret