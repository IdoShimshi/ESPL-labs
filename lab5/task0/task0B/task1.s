section .rodata
    NEW_LINE: db "",10,0
section .bss
    argc_char: resb 1
segment .text
global main

main:
    push    ebp                 
    mov     ebp, esp  
    mov edi, [ebp+8] ;argc

    mov ecx, edi
    add ecx, '0'
    mov [argc_char], ecx 
    mov eax, 4
    mov ebx, 1
    mov ecx, argc_char
    mov edx, 1
    int 0x80
    call print_newline

    mov esi, [ebp + 12] ; start argv0

    
    loop:
        cmp edi, 0
        jz post_loop
        
        sub edi, 1
    
        mov ecx, [esi]
        call my_strlen
        mov edx, eax

        mov eax, 0x4
        mov ebx, 1
        mov ecx, [esi]
        int 0x80

        call print_newline
        add esi, 4

        jmp loop

    post_loop:
        mov eax, 0
        mov     esp, ebp
        pop     ebp
        ret    

my_strlen: mov eax,1
    cont: cmp byte [ecx], 0
        jz done
        inc ecx
        inc eax
        jmp cont
    done: ret

print_newline:
    mov eax, 4
    mov ebx, 1
    mov ecx, NEW_LINE
    mov edx, 1
    int 0x80
    ret