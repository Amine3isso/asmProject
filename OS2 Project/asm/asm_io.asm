section .data
    ; Format strings
    int_format db "%d", 0
    string_format db "%s", 0
    newline db 10, 0

section .text
    extern printf
    extern scanf

; Print integer to stdout
; Input: EDI (integer to print)
print_int:
    push rbp
    mov rbp, rsp
    
    ; Call printf
    mov rsi, rdi        ; integer argument
    mov rdi, int_format ; format string
    xor rax, rax        ; no vector registers used
    call printf
    
    ; Print newline
    mov rdi, newline
    xor rax, rax
    call printf
    
    pop rbp
    ret

; Print string to stdout
; Input: RDI (string pointer)
print_string:
    push rbp
    mov rbp, rsp
    
    ; Call printf
    mov rsi, rdi        ; string argument
    mov rdi, string_format ; format string
    xor rax, rax        ; no vector registers used
    call printf
    
    ; Print newline
    mov rdi, newline
    xor rax, rax
    call printf
    
    pop rbp
    ret

; Read integer from stdin
; Output: EAX (read integer)
read_int:
    push rbp
    mov rbp, rsp
    sub rsp, 16         ; allocate space for input
    
    ; Call scanf
    lea rsi, [rbp-4]    ; address to store input
    mov rdi, int_format ; format string
    xor rax, rax        ; no vector registers used
    call scanf
    
    mov eax, [rbp-4]    ; return read value
    
    add rsp, 16
    pop rbp
    ret

; Read string from stdin
; Input: RDI (buffer pointer), RSI (buffer size)
read_string:
    push rbp
    mov rbp, rsp
    
    ; Call scanf
    mov rdx, rsi        ; buffer size
    mov rsi, rdi        ; buffer pointer
    mov rdi, string_format ; format string
    xor rax, rax        ; no vector registers used
    call scanf
    
    pop rbp
    ret