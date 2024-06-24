; subtask 1 - qsort

section .text
    global quick_sort
    ;; no extern functions allowed

quick_sort:
    ;; create the new stack frame
    enter 0, 0

    ;; save the preserved registers
    push esi
    push edi
    push ebx

    ;; recursive qsort implementation goes here
    ; buff array
    mov esi, [ebp + 8]
    ; start
    mov ebx, [ebp + 12]
    ; end
    mov edx, [ebp + 16]

    cmp ebx, edx
    jge iesire

    ; vedem pivotul ca fiind ultimul element
    mov eax, [esi + edx * 4]

    ; edi = start - 1
    ; edi = i
    mov edi, ebx
    dec edi

    ; parcurgem vectorul
    mov ecx, ebx
parcurgere:
    cmp ecx, edx
    jge schimbare_i_end

    ; daca elementul curent este mai mic decat pivotul
    cmp [esi + ecx * 4], eax
    jg fara_schimbare

    ; interschimbam buff[i] cu buff[j]
    ; i = edi
    ; j = ecx

    inc edi
    ; interschimbam buff[i] cu buff[j]
    ; push buff[i]
    push dword [esi + edi * 4]
    ; push buff[j]
    push dword [esi + ecx * 4]
    ; pop buff[i] <- buff[j]
    pop dword [esi + edi * 4]
    ; pop buff[j] <- buff[i]
    pop dword [esi + ecx * 4]


    inc ecx
    jmp parcurgere

fara_schimbare:
    inc ecx
    jmp parcurgere

schimbare_i_end:
    inc edi
    ; interschimbam buff[i + 1] cu buff[end]
    ; push buff[i + 1]
    push dword [esi + edi * 4]
    ; push buff[end]
    push dword [esi + edx * 4]
    ; pop buff[i + 1] <- buff[end]
    pop dword [esi + edi * 4]
    ; pop buff[end] <- buff[i + 1]
    pop dword [esi + edx * 4]


    ; ecx = i + 1
    mov ecx, edi

    ; salvam registrii
    push ecx
    push edx

    ; apelam quick_sort(buff, start, ecx - 1)
    dec ecx
    push ecx
    push ebx
    push esi
    call quick_sort
    ; restauram stiva
    add esp, 12

    pop edx
    pop ecx

    ; apelam quick_sort(buff, ecx + 1, end)

    ; salvam registrii
    push ecx
    push edx

    inc ecx
    push edx
    push ecx
    push esi
    call quick_sort
    ; restauram stiva
    add esp, 12

    pop edx
    pop ecx

iesire:
    ;; restore the preserved registers
    pop ebx
    pop edi
    pop esi

    leave
    ret
