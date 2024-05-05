section .data
    proc_name times 1024 db 0
    signal_num equ 13

section .text
    global _start

_start:
    ; Get command line argument
    mov rsi, [rdi + 8]
    mov rcx, rsi
    mov rax, 1
    mov rdi, proc_name
    syscall

    ; Find all processes containing the string in proc_name
    mov eax, 4
    mov rdx, 1024
    mov rsi, proc_name
    mov rdi, 0
    syscall

    ; Send a signal to each process
    mov eax, 2
    mov rdi, 0
    syscall

    ; Exit the program
    mov eax, 1
    xor rdi, rdi
    syscall
