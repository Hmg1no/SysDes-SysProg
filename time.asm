section .data
    result_format db "Payout: %d", 10, 0

section .bss
    num1 resd 1         ; Reserve space for hours worked
    num2 resd 1         ; Reserve space for salary
    result resd 1       ; Reserve space for the result

section .text
    extern printf       ; Import the printf function from C library
    global main

main:
    ; Assign values to the integers
    mov dword [num1], 15
    mov dword [num2], 15

    ; Multiply num1 by num2
    mov eax, dword [num1]
    imul dword [num2]
    mov dword [result], eax  ; Store the result
    mov ecx, [result]

    ; Print the result
   push ecx; put hamming distance in stack
	push result_format; put format string in stack
	call printf; call printf to print result

    ; Exit the program
    mov     eax, 1       ; sys_exit
    xor     ebx, ebx     ; Exit code 0
    int     0x80