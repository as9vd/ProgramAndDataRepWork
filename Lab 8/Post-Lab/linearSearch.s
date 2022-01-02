; Asadbek Shamsiev
; November 2nd, 2021
; as9vd

global linearSearch

section .text

; Parameter 1 = array base address (rdi)
; Parameter 2 = size of array (rsi)
; Parameter 3 = target value (rdx)

linearSearch:
	; # 1: Prologue
	; # I will use one of those temp registers as an index/counter (r11).
	push r11
	push r12
	push r13
	push rdi
	push rdx
	push rsi

	xor r11, r11
	xor r12, r12
	xor r13, r13

	mov r12, rdx
	mov r13, rdi			 ; I will add 4 each time to r13.
	
	jmp loop
loop: 
	; # 2: Function Body

	cmp r11, rsi 			 ; r11 is the index/counter, rsi is the size of the array.
	je noValueFound

	; # add r13, 4

	mov r13, [4*r11 + rdi] 	 ; I get a bleeding segfault everytime I try to compare [r13] with something so I will just put the value in the register now.
							 ; The value at the address we calculate (e.g. 1, 2, or whatever).

	inc r11
	cmp r13d, edx			 ; What I am tryna do: compare ((4 * r11) + rsi) with the target value
	je valueFound
	cmp r13d, edx			 ; edx is the lower 4 bytes of the rdx register (https://stackoverflow.com/questions/15442259/are-edx-and-dx-the-same-register).
	jne loop 				 ; https://www.cs.uaf.edu/2017/fall/cs301/lecture/09_11_registers.html: r13d is the 32-bit version of r13.
	
valueFound:
	mov rax, r11
	dec rax
	pop rsi
	pop rdx
	pop rdi
	pop r13
	pop r12
	pop r11
	ret
noValueFound:
	pop rsi
	pop rdx
	pop rdi
	pop r13
	pop r12
	pop r11
	mov rax, -1
	ret	