%include "../include/io.mac"

; The `expand` function returns an address to the following type of data
; structure.
struc neighbours_t
    .num_neighs resd 1  ; The number of neighbours returned.
    .neighs resd 1      ; Address of the vector containing the `num_neighs` neighbours.
                        ; A neighbour is represented by an unsigned int (dword).
endstruc

section .bss
; Vector for keeping track of visited nodes.
visited resd 10000
global visited

section .data
; Format string for printf.
fmt_str db "%u", 10, 0

section .text
global dfs
extern printf

; C function signiture:
;   void dfs(uint32_t node, neighbours_t *(*expand)(uint32_t node))
; where:
; - node -> the id of the source node for dfs.
; - expand -> pointer to a function that takes a node id and returns a structure
; populated with the neighbours of the node (see struc neighbours_t above).
; 
; note: uint32_t is an unsigned int, stored on 4 bytes (dword).
dfs:
    push ebp
    mov ebp, esp

    ; TODO: Implement the depth first search algorith, using the `expand`
    ; function to get the neighbours. When a node is visited, print it by
    ; calling `printf` with the format string in section .data.

    push edi
    push esi
    push ebx

    ; aflam nodul curent
    mov eax, [ebp + 8]
    ; vedem adresa functiei expand
    mov ebx, [ebp + 12]

    ; marcam nodul curent ca vizitat
    mov dword [visited + eax * 4], 1

    push eax
    ; afisam nodul curent
    push eax
    push fmt_str
    call printf
    ; restauram stiva
    add esp, 8
    pop eax

    ; apelam functia expand ca sa luam vecinii
    push eax
    call ebx
    ; restauram stiva
    add esp, 4

    ; nr vecini
    mov ecx, [eax]
    ; vectorul de vecini
    mov esi, [eax + 4]

    xor edx, edx
parcurgere_vecini:
    cmp edx, ecx
    jge iesire

    ; luam vecinul
    mov eax, [esi + edx * 4]
    ; trecem la pozitia urmatoare in vector
    inc edx
    ; daca nu a fost vizitat
    cmp dword [visited + eax * 4], 0
    jne parcurgere_vecini

    ; salvam registrele
    push ecx
    push edx

    ; apelam recursiv dfs
    push ebx
    push eax
    call dfs
    ; restauram stiva
    add esp, 8

    pop edx
    pop ecx

    jmp parcurgere_vecini

iesire:

    pop ebx
    pop esi
    pop edi

    leave
    ret
