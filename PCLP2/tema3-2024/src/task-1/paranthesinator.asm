; Interpret as 32 bits code
[bits 32]

%include "../include/io.mac"

section .text
; int check_parantheses(char *str)
global check_parantheses
check_parantheses:
    push ebp
    mov ebp, esp

    ; sa-nceapa concursul

    ; edx = str
    mov edx , [ebp + 8]

parcurgere_str:
    ; al = str[i]
    mov al, byte [edx]
    ; daca am ajuns la sfarsitul sirului
    cmp al, 0
    je iesire_loop

    ; adaugam parantezele de deschidere pe stiva
    cmp al, '('
    je push_stack
    cmp al, '['
    je push_stack
    cmp al, '{'
    je push_stack

    ; daca gasim o paranteza de inchidere
    cmp al, ')'
    ; verificam varful stivei == '('
    je check_stack_1
    cmp al, ']'
    ; verificam varful stivei == '['
    je check_stack_2
    ; verificam varful stivei == '{'
    cmp al, '}'
    je check_stack_3

incrementare_pointer:
    ; trecem la urmatorul caracter
    inc edx
    jmp parcurgere_str

; adaugm parantezele de deschidere pe stiva
push_stack:
    push eax
    jmp incrementare_pointer

; verificam varful stivei cu paranteza de deschidere corespunzatoare
check_stack_1:
    cmp byte [esp], '('
    ; daca se gaseste ( scoatem paranteza de pe stiva
    je pop_stack
    jmp nepotrivire

check_stack_2:
    cmp byte [esp], '['
    ; daca se gaseste [ scoatem paranteza de pe stiva
    je pop_stack
    jmp nepotrivire

check_stack_3:
    cmp byte [esp], '{'
    ; daca se gaseste { scoatem paranteza de pe stiva
    je pop_stack
    jmp nepotrivire

; daca se gaseste inchiderea buna scoatem ( sau [ sau { de pe stiva
pop_stack:
    pop ecx
    jmp incrementare_pointer

; verificam daca stiva e goala
iesire_loop:
    cmp esp, ebp
    jl nu_e_goala
    cmp esp, ebp
    je e_goala
    jmp end

; daca stiva e goala, parantezarea e corecta
e_goala:
    ; return 0
    mov eax, 0
    jmp end

; daca stiva nu e goala, parantezarea e gresita
nu_e_goala:
    ; return 1
    mov eax, 1
    jmp end

nepotrivire:
    ; return 1
    mov eax, 1
    jmp end

end:
    leave
    ret

