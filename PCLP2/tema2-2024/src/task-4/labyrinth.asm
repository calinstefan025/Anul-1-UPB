%include "../include/io.mac"

extern printf
extern position
global solve_labyrinth

section .data
    i: dd 0
    j: dd 0

section .text

; void solve_labyrinth(int *out_line, int *out_col, int m, int n, char **labyrinth);
solve_labyrinth:
    ;; DO NOT MODIFY
    push    ebp
    mov     ebp, esp
    pusha

    mov     eax, [ebp + 8]  ; unsigned int *out_line, pointer to structure containing exit position
    mov     ebx, [ebp + 12] ; unsigned int *out_col, pointer to structure containing exit position
    mov     ecx, [ebp + 16] ; unsigned int m, number of lines in the labyrinth
    mov     edx, [ebp + 20] ; unsigned int n, number of columns in the labyrinth
    mov     esi, [ebp + 24] ; char **a, matrix representation of the labyrinth
    ;; DO NOT MODIFY
   
    ;; Freestyle starts here
    mov dword [i], 0
    mov dword [j], 0
    dec ecx; m--
    dec edx; n--
    mov [ebp + 16] , ecx; m = m - 1
    mov [ebp + 20] , edx; n = n - 1

mutare_suricata:
    mov eax, dword [i] ; eax = i
    mov ebx, dword [j] ; ebx = j

    cmp eax, [ebp + 16] ; i == m - 1
    je gasit

    cmp ebx, [ebp + 20] ; j == n - 1
    je gasit

    ; actualizam labirint[i][j] = 1
    ; actualizam pentru a nu ne mai intoarce aici mai tz
    mov edi , [esi + eax*4] ; edi = labirint[i]
    add edi, ebx ; edi = labirint[i][j]
    mov byte [edi], 0x31 ; labirint[i][j] = 1

    ; verificam daca putem merge la dreapta
    mov eax, dword [i] ; eax = i
    mov ebx, dword [j] ; ebx = j
    mov edi , [esi + eax*4] ; edi = labirint[i]
    inc ebx ; j++
    add edi, ebx ; edi = labirint[i][j + 1]
    cmp byte [edi], 0x30 ; daca labirint[i][j + 1] == 0
    je mutare_dreapta

    ; verificam daca putem merge in jos
    mov eax, dword [i] ; eax = i
    mov ebx, dword [j] ; ebx = j
    inc eax ; i++
    mov edi , [esi + eax*4] ; edi = labirint[i + 1]
    add edi, ebx ; edi = labirint[i + 1][j]
    cmp byte [edi], 0x30 ; daca labirint[i + 1][j] == 0
    je mutare_jos

    ; verificam daca putem merge la stanga
    mov eax, dword [i] ; eax = i
    mov ebx, dword [j] ; ebx = j
    mov edi , [esi + eax*4] ; edi = labirint[i]
    dec ebx ; j--
    add edi, ebx ; edi = labirint[i][j - 1]
    cmp byte [edi], 0x30 ; daca labirint[i][j - 1] == 0
    je mutare_stanga

    ; verificam daca putem merge in sus
    mov eax, dword [i] ; eax = i
    mov ebx, dword [j] ; ebx = j
    dec eax ; i--
    mov edi , [esi + eax*4] ; edi = labirint[i - 1]
    add edi, ebx ; edi = labirint[i - 1][j]
    cmp byte [edi], 0x30 ; daca labirint[i - 1][j] == 0
    je mutare_sus

    jmp mutare_suricata

mutare_dreapta:
    inc dword [j] ; j++
    jmp mutare_suricata

mutare_jos:
    inc dword [i] ; i++
    jmp mutare_suricata

mutare_stanga:
    dec dword [j] ; j--
    jmp mutare_suricata

mutare_sus:
    dec dword [i] ; i--
    jmp mutare_suricata

gasit:
    mov ecx, [ebp + 8] ; ecx (auxiliar pt out_line)
    mov [ecx], eax ; out_line = i
    mov ecx, [ebp + 12] ; ecx (auxiliar pt out_col)
    mov [ecx], ebx ; out_col = j
    ;; Freestyle ends here

end:
    ;; DO NOT MODIFY
    popa
    leave
    ret
    ;; DO NOT MODIFY
