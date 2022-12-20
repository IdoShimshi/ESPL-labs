section .data
    encript_flag: db "+e"
    new_line: db "",10
    key: dd 0 ;will hold a pointer to start of key string
    key_len: dd 1 ; will hold key length
    offset: dd 1
    zibistring: db "0"
    teststring: db "test", 10,0

section .bss
    curr resb 4

section .text
global main
global system_call
extern strncmp
extern strlen

main:
    push    ebp             
    mov     ebp, esp
    mov eax, zibistring
    mov [key], eax

    mov edi, [ebp + 8] ;argc
    mov esi, [ebp + 12] ;argv
    
    loop:
        add esi, 4 ;skip filename
        dec edi
        jz loop2
        
        mov edx, [esi]
        call handle_enc_flag

        jmp loop


    loop2:

        mov eax, 3 ;read
        mov ebx, 0 ;stdin
        mov ecx, curr ;buff
        mov edx, 1 ; len
        int 0x80

        mov bl, byte [curr] 
        mov bh, byte [new_line]
        cmp bl, bh
        jz finish ;end if newline

        mov edi, [key_len] 
        sub edi, [offset]
        add edi, [key]
        mov ebx, [edi]
        and ebx, 0xff ;ebx = char in key[key_len-offset]
        sub ebx, '0' 

        mov ecx, [curr]
        add ecx, ebx
        mov [curr], ecx 
        
        mov eax, 4
        mov ebx, 1
        mov ecx, curr
        mov edx, 1
        int 0x80

        dec dword[offset]
        jz reset_offset

        jmp loop2

    finish:
        mov eax, 4
        mov ebx, 1
        mov ecx, new_line
        mov edx, 1
        int 0x80

        mov eax, 0
        mov esp, ebp
        pop ebp
        ret

reset_offset:
mov eax, [key_len]
mov [offset], eax

jmp loop2

handle_enc_flag: ; expects string that we want to check if it starts with +e to be in edx
    pushad
    push 2 ;check if first 2 chars are +e
    push edx
    push encript_flag
    call strncmp
    add esp, 12 ;fix stack

    cmp eax, 0
    popad
    jnz not_enc
    add edx, 2 ; skip the +e
    mov [key], edx ;key should point to the beginning of key string
    
    pushad
    push edx
    call strlen
    add esp, 4
    mov [key_len], eax
    mov [offset], eax
    popad
    
    not_enc:
        ret
