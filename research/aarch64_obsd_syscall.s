.section ".note.openbsd.ident", "a"
.p2align 2
.long	0x8
.long	0x4
.long	0x1
.asciz	"OpenBSD"
.long	0x0
.previous


.section .text
.global _start

_start:


	mov x8, #4
	mov x0, #1
	adr x1, strss
	mov x2, #5
	svc #0

        mov x8, #1
        svc #0


.section .data
strss: .asciz "hoi\n"
