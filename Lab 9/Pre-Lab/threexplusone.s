;; Asadbek Shamsiev
;; November 13th, 2021
;; as9vd

;; I optimised this by directly editing the rdi parameter instead of pushing it to a dummy register and editing it that way.
;; I also used shift right instead of dividing by 2, because division is expensive.

section .text

global threexplusone

;; Parameter 1 is the input (rdi).
;; "Parameter 2" is the amount of times the subroutine is called (rsi); this can be dealed with in the C++ function so forget about it.
;; Return type is int.

threexplusone:
	xor r10, r10
	xor rax, rax
	jmp checking
checking:
	cmp rdi, 1	
	je end
	test rdi, 1 ;; https://stackoverflow.com/questions/49116747/assembly-check-if-number-is-even: helpful resource.
	jnz odd		 
	jz even
even:
	shr rdi, 1
	inc r10
	push r10
	call threexplusone
	pop r10
	add r10, rax
	jmp end
odd:
	imul rdi, 3
	add rdi, 1
	inc r10
	push r10
	call threexplusone
	pop r10
	add r10, rax
	jmp end
end:
	mov rax, r10
	ret