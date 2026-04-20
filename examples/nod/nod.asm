
section .text
GLOBAL nod
nod:
    push ebp
    mov ebp,esp
    mov eax, dword[ebp+8] ;a
    sub esp,8
    test eax,eax
    jz .ab_plus
    mov ecx, dword[ebp+12] ;b
    test ecx,ecx
    jz .ab_plus
    cmp eax,ecx
    jng .skip
    cdq
    idiv ecx
    mov dword[esp],edx ;a%b
    mov dword[esp+4],ecx ;b
    call nod
    jmp .finish
.skip:
    mov dword[esp],eax
    mov eax, ecx
    cdq
    idiv dword[ebp+8] ;b%a
    mov dword[esp+4], edx
    call nod
    jmp .finish
        
.ab_plus:
    add eax,ecx
.finish:
    add esp,8
    pop ebp
    ret
  