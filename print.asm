 section .text
;;this writes to files correcly haha
    global main

    main:

    mov eax,5
    mov ebx, pathname
    mov ecx, 101o
    mov edx, 700o
    int 80h

    mov ebx, eax
    mov eax,4
    mov ecx, hello
    mov edx,15
    int 80h

    mov eax,5
    mov ebx, pathname
    mov ecx, 101o
    mov edx, 700o
    int 80h

    mov ebx, eax
    mov eax,4
    mov ecx, goodbye
    mov edx,15
    int 80h
    
    mov eax,1            ; 'exit' system call
	mov ebx,0            ; exit with error code 0
	int 80h              ; call the kernel 

    section .data
    prompt1: db "Please enter the file name: ",10
    len1: equ $-prompt1
    format: db "%d",10,0
    delimiter: db 10 ;ascii for newline '\n'    
    filename: times 256 db 0    ;Allocate buffer of 256 bytes
	pathname: dd "/afs/umbc.edu/users/h/j/hj69411/home/cmpe310/proj4/fix.txt";output file
    hello:     db "Hello Zorld!",0AH,0DH,"$"
	helloLen:  equ $-hello
    goodbye: db "Hello Porld!",0AH,0DH,"$"

   
section .bss
    buffer: resd 8