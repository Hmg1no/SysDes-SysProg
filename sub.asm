extern printf
global main
;;practice code for subtracting integers
section .bss
  num1: resb 4
  num2: resb 4
section .data
  format_number: db "%f", 10, 0
section .text
main:

  mov dword [num1], 90
  mov dword [num2], __float32__(10.00)

  sub esp, 8
  fld dword [num2]
  fisub dword [num1]
  fstp qword [esp]
  push format_number
  call printf
  add esp, 12

ret