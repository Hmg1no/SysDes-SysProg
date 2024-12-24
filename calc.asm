extern printf
segment .data
	
	;;sign in/sign out
;;make a menu
;;sign in = type first name, type last name, time 12:32, export to file
;;sign out = type first name type last name, time 12:42, edit file
;;calculate = type name, locate them sign in/out, subtraction, multiply by hourly rate
section .data
prompt1: db "Please enter the first name: ",10
len1: equ $-prompt1
prompt2: db "Please enter last name: ",10
len2: equ $-prompt2
prompt3: db "Please enter time (Hour:Minute): ", 10
len3: equ $-prompt3
fname: times 256 db 0    ;Allocate buffer of 256 bytes
lname: times 256 db 0    ;Allocate buffer of 256 bytes
time: times 6 db 0 ;Allocate buffer of 6 bytes 
welcome: db "Welcome to Project Timesheet",10
			db "    [0] Sign-in        ",10
				db "    [1] Sign-Out       ",10
				db "    [2] Calculate Pay  ",10
				db "    [3] Quit           ",10	
lenMenu: 		equ $ - welcome
option: times 4 db 0
pathname: dd "/afs/umbc.edu/users/h/j/hj69411/home/cmpe310/proj4/names.txt";output file

section .text
	global main

main:

	push ebp ; set up stack frame
	mov ebp,esp
	mov eax,4 ; use the write function
	mov ebx,1 ; use the standard output
	mov edx,lenMenu ; set the number of characters to print
	mov ecx,welcome ; string to print
	int 0x80 ; call kernel to print the message
	mov eax,3 ; use the read function
	mov ebx,0 ; use the standard input
	mov ecx,option ; load in string1
	mov edx,4 ; read at most 255 characters
	int 0x80 ; call kernel to read the string
	mov BYTE [option + eax -1], 0 ; insert string terminator
	mov eax,4 ; use the write function
	mov ebx,1 ; use the standard output
	mov edx,len1 ; set the number of characters to print
	mov ecx,prompt1 ; string to print
	int 0x80 ; call kernel to print the message
	mov eax,3 ; use the read function
	mov ebx,0 ; use the standard input
	mov ecx,fname ; load in string1
	mov edx,255 ; read at most 255 characters
	int 0x80 ; call kernel to read the string
	mov BYTE [fname + eax -1], 0 ; insert string terminator
	mov eax,4 ; use the write function
	mov ebx,1 ; use the standard output
	mov edx,len2 ; set the number of characters to print
	mov ecx,prompt2 ; string to print
	int 80h ; call kernel to print the message
	mov eax,3 ; use the read function
	mov ebx,0 ; use the standard input
	mov ecx,lname ; load in string2
	mov edx,255 ; read at most 255 characters
	int 0x80 ; call kernel to read the string
	mov BYTE [lname + eax -1], 0 ; insert string terminator
    mov eax,4 ; use the write function
	mov ebx,1 ; use the standard output
	mov edx,len3 ; set the number of characters to print
	mov ecx,prompt3 ; string to print
	int 80h ; call kernel to print the message
	mov eax,3 ; use the read function
	mov ebx,0 ; use the standard input
	mov ecx,time ; load in string2
	mov edx,6 ; read at most 255 characters
	int 0x80 ; call kernel to read the string
	mov BYTE [time + eax -1], 0 ; insert string terminator

exit:
    mov esp,ebp ; takedown stack frame
	pop ebp
	mov eax,0 ; normal, no error, return value
	ret ; return