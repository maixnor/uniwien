section .data
    proc_name db "spotify", 0
    SIGKILL equ 9 

section .text
    global _start

_start:
    ; Open the /proc directory
    mov rdi, proc_dir
    call opendir

    ; Loop through directory entries
loop_entries:
    ; Read the next directory entry
    mov rdi, rax    ; Directory stream from opendir
    call readdir
    test rax, rax  ; Check if readdir returned NULL
    jz end_loop    ; If NULL, end the loop

    ; Check if the entry is a directory and skip . and ..
    cmp qword [rdi], '.' | ('.' << 8) | ('.' << 16) | ('/' << 24)
    jz loop_entries  ; Skip . and ..

    ; Convert directory name to integer (PID)
    call atoi64
    mov rsi, rax  ; rsi contains the PID

    ; Open the cmdline file for the process
    mov rdi, rsi  ; rdi contains the PID
    call open_cmdline

    ; Read the cmdline file
    mov rdi, rax  ; File descriptor from open_cmdline
    lea rsi, [rsp + cmd_buffer]
    mov rdx, cmd_buffer_size
    call read_cmdline

    ; Check if the process name is in the cmdline
    mov rdi, rax  ; Number of bytes read from read_cmdline
    lea rsi, [rsp + cmd_buffer]
    lea rdx, [proc_name]
    call strstr
    test rax, rax
    jz loop_entries  ; Process name not found, continue loop

    ; Terminate the process
    mov rdi, rsi  ; rdi contains the PID
    mov rsi, SIGKILL
    call kill

    ; Print success message
    mov rdi, rsi  ; rdi contains the PID
    call print_success

    ; Continue loop
    jmp loop_entries

end_loop:
    ; Close the /proc directory
    mov rdi, proc_dir
    call closedir

    ; Exit
    mov rdi, 0
    call exit

section .bss
    proc_dir resq 1
    cmd_buffer resb 256
    cmd_buffer_size equ 256

extern opendir, readdir, closedir, atoi64, open_cmdline, read_cmdline, kill, exit, printf

%macro print_success 1
    mov rdi, success_msg
    mov rsi, %1
    xor rax, rax
    call printf
%endmacro

section .data
    success_msg db "Process %d killed successfully.", 10, 0

section .text
    global strstr

strstr:
    push rbp
    mov rbp, rsp
    mov rsi, rdi
    mov rdi, rdx
    call _strstr
    leave
    ret

section .text
    global _strstr

_strstr:
    push rsi
    push rdi
    push rcx
    push rdx

.loop:
    mov rcx, rsi
    mov rdx, rdi
    mov al, [rcx]
    test al, al
    jz .found
    cmp al, [rdx]
    jne .next
    inc rsi
    inc rdi
    jmp .loop

.next:
    pop rdx
    pop rcx
    pop rdi
    pop rsi
    inc rdi
    test byte [rdi-1], [rdi-1]
    jnz .loop
    xor rax, rax
    ret

.found:
    pop rdx
    pop rcx
    pop rdi
    pop rsi
    mov rax, rdi
    ret

