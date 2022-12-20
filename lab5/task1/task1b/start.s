section .data
    encript_flag: db "+e"
    input_flag: db "-i"
    output_flag: db "-o"
    new_line: db "",10
    key: dd 0 ;will hold a pointer to start of key string
    key_len: dd 1 ; will hold key length
    offset: dd 1
    zibistring: db "0"
    teststring: db "test", 10,0
    input: dd 0
    output: dd 1

section .bss
    curr resb 4

section .text
global _start
global system_call
global main
extern strncmp
extern strlen
_start:
    pop    dword ecx    ; ecx = argc
    mov    esi,esp      ; esi = argv
    ;; lea eax, [esi+4*ecx+4] ; eax = envp = (4*ecx)+esi+4
    mov     eax,ecx     ; put the number of arguments into eax
    shl     eax,2       ; compute the size of argv in bytes
    add     eax,esi     ; add the size to the address of argv 
    add     eax,4       ; skip NULL at the end of argv
    push    dword eax   ; char *envp[]
    push    dword esi   ; char* argv[]
    push    dword ecx   ; int argc

    call    main        ; int main( int argc, char *argv[], char *envp[] )

    mov     ebx,eax
    mov     eax,1
    int     0x80
    nop
        
system_call:
    push    ebp             ; Save caller state
    mov     ebp, esp
    sub     esp, 4          ; Leave space for local var on stack
    pushad                  ; Save some more caller state

    mov     eax, [ebp+8]    ; Copy function args to registers: leftmost...        
    mov     ebx, [ebp+12]   ; Next argument...
    mov     ecx, [ebp+16]   ; Next argument...
    mov     edx, [ebp+20]   ; Next argument...
    int     0x80            ; Transfer control to operating system
    mov     [ebp-4], eax    ; Save returned value...
    popad                   ; Restore caller state (registers)
    mov     eax, [ebp-4]    ; place returned value where caller can see it
    add     esp, 4          ; Restore caller state
    pop     ebp             ; Restore caller state
    ret                     ; Back to caller


main:
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
        mov edx, [esi]
        call handle_input_flag
        mov edx, [esi]
        call handle_output_flag

        jmp loop

    loop2:
        mov eax, 3 ;read
        mov ebx, [input] ;stdin
        mov ecx, curr ;buff
        mov edx, 1 ; len
        int 0x80

        cmp eax,0
        jle finish

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
        mov ebx, [output]
        mov ecx, curr
        mov edx, 1
        int 0x80

        dec dword[offset]
        jz reset_offset

        jmp loop2

    finish:
        mov eax, 4
        mov ebx, [output]
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

handle_input_flag: ; expects string that we want to check if it starts with -i to be in edx
    pushad
    push 2 ;check if first 2 chars are -i
    push edx
    push input_flag
    call strncmp
    add esp, 12 ;fix stack

    cmp eax, 0
    popad
    jnz not_inp
    add edx, 2 ; skip the -i
    
    mov eax, 5 ;open
    mov ebx, edx ;filename
    mov ecx, 2 ;read write
    mov edx, 0777 ;read,write,execute by all
    int 0x80

    mov [input], eax
    
    not_inp:
        ret

handle_output_flag: ; expects string that we want to check if it starts with -o to be in edx

    pushad
    push 2 ;check if first 2 chars are -o
    push edx
    push output_flag
    call strncmp
    add esp, 12 ;fix stack

    cmp eax, 0
    popad
    jnz not_out
    add edx, 2 ; skip the -o


    mov eax, 5 ;open
    mov ebx, edx ;filename
    mov ecx, 1024 ;append
    or ecx, 1 ;and read write
    or ecx, 64 ;and create 
    mov edx, 0777 ;read,write,execute by all
    int 0x80

    mov [output], eax
    
    not_out:
        ret