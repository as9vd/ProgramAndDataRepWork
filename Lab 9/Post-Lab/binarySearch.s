;; Asadbek Shamsiev
;; November 17th, 2021
;; as9vd

section .text

global binarySearch

;; Parameter 1 (rdi) = pointer to int array.
;; Parameter 2 (rsi) = beginning of array (index).
;; Parameter 3 (rdx) = end of array (index).
;; Parameter 4 (rcx) = target element.

;; Get the middle value each time, and check if the target is greater/less than the middle. Jump to the appropriate body depending on the result.

binarySearch:
	xor r10, r10			;; Reset these dummy registers at the beginning of each iteration.
	xor r11, r11
	xor rax, rax
	jmp checking
checking:
	cmp rsi, rdx			;; while (low <= high)
	jg unsuccessfulEnd		;; If it is greater than, then the input is either screwed, or the thing is not in the list.

	mov r10, rdx 			;; Moving the last index to r10, adding the initial, and dividing it by 2 to get the middle index.
	add r10, rsi
	shr r10, 1
	mov r11, [rdi + 4*r10]	;; Getting the value of the middle index.
	cmp ecx, r11d			;; Otherwise you get two numbers within the 64 bits, like post-lab 8. Gotta use 32 bits unfortunately.
	je successfulEnd
	jl lessThan				;; If the target element is less than the middle element, jump to the lessThan body.
	jg greaterThan			;; If the target element is greater than the middle element, jump to the greaterThan body.
lessThan:
	mov rdx, r10			;; high = mid - 1
	sub rdx, 1
	jmp binarySearch
greaterThan:
	mov rsi, r10			;; low = mid + 1
	inc rsi
	jmp binarySearch
unsuccessfulEnd:
	mov rax, -1				;; return -1
	ret
successfulEnd:
	mov rax, r10			;; return mid
	ret