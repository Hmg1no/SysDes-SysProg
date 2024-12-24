section .data:

    prompt2 dd "The value of this string is: ", 0
    fmt2 db "The total value of all the sums is: $d"
    filename db "./randomInt10.txt"
    bufsize dw 1024


section .bss

readp resb 4
ltoread resb 2000 ;for the file name 
buffer: resb 2000 ;the max amount of character to be read from file
sum resb 4 ;the amount of space to calculate the sum


section .text
    global _start

_start: 
    jmp open
    

; Add missing sections (open, read, convert, print_sum) as needed
		
open:
;open the text file to read from:

    
    mov ebx, filename ; const char *filename
    mov eax, 5 ;set to open file 
    mov ecx, 0 ; set to read only mode
    int 80h
    
    jmp read

read: 

    mov [readp], ebx ; allows to stores the file descriptor into the memory location

    mov eax, 3 ; sys_read call
    mov ebx, eax ; set readp as input for read operation
    mov ecx, buffer ;load memory address of where to store data 
    mov edx, ltoread ; Max amount of bytes to read 
    int 80h

    jmp write

convert:
;convert each string to a number by parsing and shifting for numeric value 

    mov esi, edx
    lodsb               ; Load the next character into AL
    sub al, '0'         ; Convert ASCII to integer ('0' -> 0, '1' -> 1, ..., '9' -> 9)


    test al, al         ; Check if we've reached the end of the string (null terminator)

    jnz convert         ; If not, continue the loop

write:

    mov eax, 4 ;call for sys_write 
    mov ebx, 1 ;set readp for standard output 
    mov ecx, buffer ; load data read to be written to output
    mov edx, ltoread ; Number of bytes to write
    int 80h

resetReg:

;Needed in order to effectively convert asci values

    xor dx, dx ; initialize for division DX: AX/BX
    mov bx, 10
    xor cx, cx ; act as a counter, need to reset
    mov esi, buffer ;point esi to buffer


convertA:

    div bx ; AX is quotient, remainder is in DX (0-9)
    push dx ; save remainder to memory
    test ax, ax ; see if zero 
    je exit ; if ax is 0, jump to exit
    jl exit ; 
    jnz convertA ; No, use as the number to divide by on next loop

convertB:

    ;convert each string to a number by parsing and shifting for numeric value 
    ;This portion is the dividedend

    pop dx ;should be first on the stack
    add dl, "0" ;Turn into character [0,9] -> ["0", "9"]
    mov eax, 4 ;sys_write call
    mov ebx, 1; file descriptor 1 for output
    mov [buffer], dl ; move the character to the buffer

    int 0x80 
    loop convertB

write2:
    add [sum], dx
    add [sum], bx
    mov eax, 4  ; System call number for sys_write
    mov ebx, 1  ; File descriptor for standard output
    mov ecx, fmt2  ; Move the address of the format string into ECX
    int 0x80

    mov eax, 4  ; System call number for sys_write
    mov ebx, 1  ; File descriptor for standard output
    mov edx, [sum]  ; Move the sum into EDX
    int 80h  ; Interrupt to invoke the system call
    
exit:

    mov eax, 6  ;close the file 
    mov ebx, [readp]
    mov eax, 1  ;exit
    mov ebx, 0  
    int 0x80
