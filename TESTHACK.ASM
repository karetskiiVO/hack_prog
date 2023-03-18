.286
.model tiny
.code
org 100h
Start:
xor ax, ax
mov bx, 01d8h
jmp bx
	
end Start