global _EFLAGS
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
	
global _RAX
_RAX:
	ret

global _RBX
_RBX:
	mov rax, rbx
	ret

global _RCX
_RCX:
	mov rax, rcx
	ret

global _RDX
_RDX:
	mov rax, rdx
	ret

global _RSP
_RSP:
	mov rax, rsp
	ret

global _RBP
_RBP:
	mov rax, rbp
	ret

global _RSI
_RSI:
	mov rax, rsi
	ret

global _RDI
_RDI:
	mov rax, rdi
	ret


global _RSS
_RSS:
	mov rax, ss
	ret

global _RCS
_RCS:
	mov rax, cs
	ret

global _RDS
_RDS:
	mov rax, ds
	ret

global _RES
_RES:
	mov rax, es
	ret

global _RFS
_RFS:
	mov rax, fs
	ret

global _RGS
_RGS:
	mov rax, gs
	ret
