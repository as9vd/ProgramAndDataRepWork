; Asadbek Shamsiev
; November 2nd, 2021
; as9vd

; University of Virginia
; CS 2150 In-Lab 8
; Spring 2018
; mergeSort.s	

	global mergeSort
	global merge

	section .text

; Parameter 1 is a pointer to the int array (rdi)
; Parameter 2 is the left index in the array (rsi)
; Parameter 3 is the right index in the array (rdx)
; Return type is void 

mergeSort:
	; 1: Prologue
	jmp body
body:
	; 2: Function body

	; 1/3: First Half

	cmp rsi, rdx
	jge end 		; if the two indexes are the same (e.g. (0, 0)), then we can jump and return the return address
	mov r12, rsi 	; r12 is rsi, i cant keep up with this pushing and popping carry on. far too much tracking needed for that
	mov	r13, rdx 	; r13 is rdx
	add r13, rsi 	
	shr r13, 1 		; add start to right index, divide by 2, and you get the middle
	push rdx		; save these values because they might be edited later
	push rsi
	push r13
	push r12
	mov rdx, r13
	call mergeSort ; we will keep calling this function until the array is so small its comparing one element
	pop r12
	pop r13
	pop rsi
	pop rdx

	; 2/3: Second Half

	push rdx 		; we pushed it as the end index earlier, so it holds the end index as its value
	push rsi
	push r13		; mid
	push r12		; rsi (0)
	inc r13			; second half, mid + 1
	mov rsi, r13	; move mid + 1 to rsi so we can actually compare the sh** properly 
	call mergeSort	; rdx is still the end because i havent actually touched it in this program...
	pop r12
	pop r13
	pop rsi
	pop rdx

	; 3/3: Actually Merging The Two Halves Together
	; rsi = left, rdx = middle, rcx = right
	
	mov rcx, rdx	; moving end index to rcx
	mov rdx, r13	; transfering middle value to rdx

	push r10
	push r11
	call merge
	pop r11
	pop r10

end:
	; 3: Epilogue
	ret



; Parameter 1 is a pointer to the int array (rdi)
; Parameter 2 is the left index in the array (rsi)
; Parameter 3 is the middle index in the array (rdx)
; Parameter 4 is the right index in the array (rcx)
; Return type is void 
merge:
	; Save callee-save registers
	; Store local variables 
	push rbx			; int i
	push r12			; int j
	push r13			; int k
	push r14			; int n1
	push r15			; int n2
	
	mov r14, rdx			; n1 = mid - left + 1
	sub r14, rsi
	inc r14

	mov r15, rcx			; n2 = right - mid 
	sub r15, rdx

	lea r11, [r14+r15]		; r11 = rsp offset = 4(n1 + n2)
	lea r11, [4*r11]		
	sub rsp, r11			; allocate space for temp arrays

	mov rbx, 0			; i = 0
	mov r12, 0			; j = 0
	
; Copy elements of arr[] into L[]	
copyLloop:
	cmp rbx, r14			; is i >= n1?
	jge copyRloop
					; L[i] = arr[left + i]
	lea r10, [rsi+rbx]		
	mov r10d, DWORD [rdi+4*r10]	; r10 = arr[left + i]
	mov DWORD [rsp+4*rbx], r10d	; L[i] = r10
	inc rbx				; i++
	jmp copyLloop

; Copy elements of arr[] into R[]
copyRloop:
	cmp r12, r15			; is j >= n2?
	jge endcopyR
 					; R[j] = arr[mid + 1 + j]
	lea r10, [rdx+r12+1]	
	mov r10d, DWORD [rdi+4*r10]	; r10 = arr[mid + 1 + j]
	lea rax, [r12+r14]		
	mov DWORD [rsp+4*rax], r10d	; R[j] = r10
	inc r12				; j++
	jmp copyRloop

endcopyR:	
	mov rbx, 0			; i = 0
	mov r12, 0			; j = 0
	mov r13, rsi			; k = left

; Merge L[] and R[] into arr[]
mergeLoop:
	cmp rbx, r14			; is i >= n1 or j >= n2?
	jge loopL
	cmp r12, r15
	jge loopL
	lea r10, [r12+r14]
	mov r10d, DWORD [rsp+4*r10] 	; r10d = R[j]
	cmp DWORD [rsp+4*rbx], r10d	; is L[i] <= R[j]?
	jle if
	mov DWORD [rdi+4*r13], r10d	; arr[k] = R[j]
	inc r12				; j++
	jmp endif 
if:
	mov r10d, DWORD [rsp+4*rbx] 
	mov DWORD [rdi+4*r13], r10d	; arr[k] = L[i] 
	inc rbx				; i++
endif:	
	inc r13				; k++	
	jmp mergeLoop
	
; Copy elements of L[] into arr[]
loopL:				
	cmp rbx, r14			; is i >= n1?
	jge loopR
	mov r10d, DWORD [rsp+4*rbx] 
	mov DWORD [rdi+4*r13], r10d	; arr[k] = L[i]
	inc rbx				; i++
	inc r13				; k++
	jmp loopL

; Copy elements of R[] into arr[]
loopR:	
	cmp r12, r15			; is j >= n2?
	jge endR
	lea r10, [r12+r14]
	mov r10d, DWORD [rsp+4*r10] 	
	mov DWORD [rdi+4*r13], r10d	; arr[k] = R[j]

	inc r12				; j++
	inc r13				; k++
	jmp loopR
	
endR:
	; deallocate temp arrays
	; restore callee-save registers
	add rsp, r11	
	pop r15			
	pop r14
	pop r13
	pop r12
	pop rbx
	ret