; subtask 2 - bsearch

section .text
    global binary_search
    ;; no extern functions allowed

binary_search:
    ;; create the new stack frame
    enter 0, 0

    ;; save the preserved registers
    push esi
    push edi
    push ebx

    ;; recursive bsearch implementation goes here

    ;; ecx = buff array
    ;; edx = needle

    ;; edi = start
    mov edi, [ebp + 8]
    ;; esi = end
    mov esi, [ebp + 12]

    ; verificam daca start > end
    cmp edi, esi
    jg not_found

    ; calculam mijlocul
    ; mij = 0
    xor ebx, ebx
    ; mij = mij + end
    add ebx, esi
    ; mij = end + start
    add ebx, edi
    ; mij = (end + start) / 2
    shr ebx, 1

    ; eax = buff[mij]
    mov eax, [ecx + ebx * 4]

    ; verificam daca am gasit elementul
    cmp eax, edx
    je found
    jl right
    jg left

left:
    ; salvam end
    push esi

    ; end = mij
    mov esi, ebx
    ; end = mij - 1
    dec esi

    push esi
    push edi
    call binary_search
    ; restauram stiva
    add esp, 8

    ; revenim la vechiul end
    pop esi
    jmp end

right:
    ; salvam start
    push edi

    ; start = mij
    mov edi, ebx
    ; start = mij + 1
    inc edi

    push esi
    push edi
    call binary_search
    ; restauram stiva
    add esp, 8

    ; revenim la vechiul start
    pop edi
    jmp end

found:
    ; returnam mijlocul
    mov eax, ebx
    jmp end

not_found:
    ; returnam -1
    mov eax, -1
    jmp end

end:
    ;; restore the preserved registers
    pop ebx
    pop edi
    pop esi

    leave
    ret
