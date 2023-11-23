section .data
    msg db 'Hello from assembly!', 0
    asmMsg db 'This is the test folder where you can test stuff.', 0

section .text
    global asm_function
    extern puts

asm_function:
    ; Msg
    sub rsp, 28
    mov rcx, msg
    call puts
    add rsp, 28

    ; Asm Msg
    sub rsp, 28
    mov rcx, asmMsg
    call puts
    add rsp, 28

    ; Exit
    mov eax, 60
    xor edi, edi
    syscall