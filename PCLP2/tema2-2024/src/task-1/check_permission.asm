%include "../include/io.mac"

extern ant_permissions

extern printf
global check_permission

section .text

check_permission:
    ;; DO NOT MODIFY
    push    ebp
    mov     ebp, esp
    pusha

    mov     eax, [ebp + 8]  ; id and permission
    mov     ebx, [ebp + 12] ; address to return the result
    ;; DO NOT MODIFY
   
    ;; Your code starts here

    ; shiftam la dreapta cu 24 ca sa ramana doar id-ul furnicii
    mov edx, eax
    shr edx, 24 ; edx = id furnica

    ; shiftam la stanga si apoi la drapta cu 8 ca sa facem 0 primii 8 biti 
    mov esi, eax
    shl esi, 8
    shr esi, 8 ; esi = salile cerute

    ; edi = salile la care are permisiuni furnica
    mov edi, dword [ant_permissions + edx * 4]
  
    ; in eax vom avea doar salile in care avem acces dar sunt si cerute
    mov eax, esi ; eax = copie salile cerute pentru a nu strica esi
    and eax, edi ; vedem care biti de 1 sunt in ambele registre

    ; vedem daca toate salile permise si cerute coincid cu cele cerute
    cmp eax, esi ; daca toti bitii de 1 din eax sunt si in esi atunci res = 1
    je toate_salile
    
    mov dword [ebx], 0 ; daca nu are permisiuni pt toate salile punem 0 in res
    jmp end

toate_salile:
    mov dword [ebx], 1 ; are permisiuni pt toate salile
    jmp end

end:

    ;; Your code ends here
    
    ;; DO NOT MODIFY

    popa
    leave
    ret
    
    ;; DO NOT MODIFY
