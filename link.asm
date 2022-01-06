global _RAX
global _RBX
global _RCX
global _RDX
global _RSP
global _RBP
global _RSI
global _RDI

global _RSS
global _RCS
global _RDS
global _RES
global _RFS
global _RGS

global _EFLAGS

_RAX:
	ret

_RBX:
	mov rax, rbx
	ret

_RCX:
	mov rax, rcx
	ret

_RDX:
	mov rax, rdx
	ret

_RSP:
	mov rax, rsp
	ret

_RBP:
	mov rax, rbp
	ret

_RSI:
	mov rax, rsi
	ret

_RDI:
	mov rax, rdi
	ret


_RSS:
	mov rax, ss
	ret

_RCS:
	mov rax, cs
	ret

_RDS:
	mov rax, ds
	ret

_RES:
	mov rax, es
	ret

_RFS:
	mov rax, fs
	ret

_RGS:
	mov rax, gs
	ret

_EFLAGS:
	pushf  			; push eflags into stack
	pop rax 		; pop it into rax
	ret

global Return_4x_16bit_arguments

Return_4x_16bit_arguments:
	mov rax, rdi
	shl rax, $10
	add rax, rsi
	shl rax, $10
	add rax, rdx
	shl rax, $10
	add rax, rcx
	ret