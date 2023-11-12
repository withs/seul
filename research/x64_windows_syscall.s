section text
global _start

_start:

	sub rsp, 0x20
	mov qword rcx, text
	mov qword rdx, text_len
	call write_to_console
	add rsp, 0x20

	; termiate
	sub rsp, 0x20
	
	mov rax, 0x53
	mov r10, -1
	mov rdx, 1
	syscall
	
write_to_console:
	
	sub rsp, 0x70

	mov qword[rsp + 0x60], rcx
	mov qword[rsp + 0x68], rdx

	; stdout
	mov rcx, gs:0x60
	mov rcx, [rcx + 0x20]
	mov rcx, [rcx + 0x28]

	; syscall num
	mov rax, 0x8

	mov r10, rcx
	mov rdx, 0
	mov r8, 0
	mov r9, 0

	; isb
	lea rbx, [rsp + 0x50]
	mov qword[rsp + 0x28], rbx

	; buff
	mov rbx, [rsp + 0x60]
	mov qword[rsp + 0x30], rbx

	; len
	mov rbx, [rsp + 0x68]
	mov qword[rsp + 0x38], rbx

	; byte off & key
	mov rbx, 0
	mov qword[rsp + 0x40], rbx
	mov qword[rsp + 0x48], rbx
	syscall

	add rsp, 0x70


; nasm -g -f win64 .\wrs.s
; clang -fuse-ld=lld-link --for-linker "/entry:_start" --for-linker "/subsystem:console" -nostdlib .\wrs.obj -o wrs.exe

section data
text db "hello", 0
text_len equ $-text