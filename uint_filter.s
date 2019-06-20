;rdi - input tab
;rsi - output tab
;rdx - width
;rcx - height
;r8 - mask

section .text
	global max_filt_u;add_two

max_filt_u:
	push rbp
	mov rbp, rsp
	push r9		;row index of filtered pixel
	push r10	;colum index of filtered pixel
	push r11	;row iter on mask
	push r12	;col iter on mask
	push r13	;max value found in mask
	push r14	;column width*3
	push r15	;additional register
	;rdx		; mask * 3

init_vals:
	xor r14, r14
	lea r14, [rdx+2*rdx]	;init column width * 3
	xor rdx, rdx
	lea rdx, [r8+2*r8]		;init mask * 3
	xor r15, r15			;init column iterator * 3

	xor r9, r9				;init row_idx of filtered pixel
row_idx_loop:	;loop over columns of filtered pixels
;remember to check if r9 is out of bounds!

	xor r10, r10

col_idx_loop:				;init max value of filtered pixel, go through the mask
;remember to check if r10 is out of bounds!
	xor r13, r13			;max = 0

	xor r11, r11
	mov r11, r9
	sub r11, r8				;init row_iter = row_idx - mask

	cmp r11, 0				;if row_idx is outside of picture
	jge row_iter_loop
	xor r11, r11

row_iter_loop:
;remember to check if r11 is equal to row_idx+mask or picture heigt!
	xor r12, r12
	mov r12, r10
	sub r12, rdx			;init col_iter = col_idx - mask*3

	cmp r12, 0
	jge col_iter_loop

col_iter_adjust:			;if iterator is outside of image, keep adjusting untill it gets inside
	add r12, 3				;col_iter = col_iter + 3
	cmp r12, 0
	jl	col_iter_adjust

col_iter_loop:
;remember to check if r12 is bigger than col_idx+mask*3!

	xor r15, r15			;calculate offset from beginning of table
	mov r15, r11
	imul r15, r14
	add r15, r12
	xor rax, rax
	mov al, [rdi+r15]		;get value o pixel in mask on coordinates(row_iter, col_iter)

svn:	cmp eax, r13d
eit:	jle col_iter_continue	;if no bigger value found, continue without changing max

nin:	xor r13, r13
	mov r13b, al			;if new checked value is bigger than max, replace

col_iter_continue:

	add r12, 3

	cmp r12, r14			;if col_iter == width*3
	jge row_iter_continue


	xor r15, r15
	lea r15, [r10 + rdx]	;if col_iter <= row_idx+mask*3

	cmp r12, r15
    jg row_iter_continue
	jmp col_iter_loop

row_iter_continue:
	inc r11

	cmp r11, rcx			;if row_iter == height
	jge col_idx_continue

	xor r15, r15
	lea r15, [r9 + r8]

	cmp r11, r15			;if row iter == row_idx+mask
	jg col_idx_continue

	jmp row_iter_loop

col_idx_continue:

	mov [rsi], r13b			;move max value after filtering mask
	inc rsi
	inc r10

	cmp r10, r14
	jl col_idx_loop		;if col_idx == width*+3

row_idx_continue:
	inc r9

	cmp r9, rcx
	jl	 row_idx_loop




exit:
	pop r15
	pop r14
	pop r13
	pop r12
	pop r11
	pop r10
	pop r9
	mov rsp, rbp
	pop rbp
	ret
;add_two:
;	push rbp
;	mov rbp, rsp
;	push r11
;	push r12
;	push r13
;
;copy_digits:
;	xor r11, r11
;	lea r11, [rdi]	;a
;	xor r12, r12
;	lea r12, [rsi]	;b
;
;add_numbers:
;	xor r13, r13
;	lea r13, [r11+r12]
;	mov rdx, r13
;
;exit:
;	pop r13
;	pop r12
;	pop r11
;	mov rsp, rbp
;	pop rbp
;	ret