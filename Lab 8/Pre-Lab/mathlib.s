; Asadbek Shamsiev
; October 31st, 2021
; as9vd

; rdi = parameter 1, rsi = parameter 2


section .text

global product
global power

product: 
	xor	rax, rax	 ; zero out the return register
	xor r10, r10	 ; zero out the counter
start1: 
	cmp r10, rsi 	 ; check if counter equals parameter two
	je done1
	add rax, rdi	
	inc r10
	jmp start1
done1: 
	ret

power:
	; xor r10, r10	 ; zero out the counter
	; push rdi
	; push r10
	; mov r10, 1		 ; a default dd value for one

	mov rax, 1	; because anything to the zeroth is one  
	cmp rsi, 0	; easier to compare up here...
	je done2
start2:
	; cmp rsi, 0 		 ; check if counter equals base case
	; je done2		 ; if so, skip to end
	; dec rsi 		 ; decrement that sh** so the thing doesnt recurse forever
	; call _power
	; pop rdi
	; call _product
	; ret


	dec rsi
	call power		; recurses basically. checks the rsi value above
	mov rsi, rax	; rsi is the second parameter, and rax is the return value. this second parameter calls the product function with the updated value from the _power function a line above
	call product	; finally when at base case
	
done2:
	; mov rax, rdi
	; pop rdi
	; pop r10
	ret