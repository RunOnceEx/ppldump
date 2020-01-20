extern WindowsEntrypoint
global StackAlign

segment .text

StackAlign:
	push rsi
	mov rsi, rsp
	and rsp, 0FFFFFFFFFFFFFFF0h
	sub rsp, 020h
	call WindowsEntrypoint
	mov rsp, rsi
	pop rsi
	ret 
