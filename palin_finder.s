.equ	LEDR, 0xFF200000

.text
.global _start

/*
 * Set LEDs
 */
leds_clear:
	ldr r0, =LEDR
	mov r1, #0
	str r1, [r0]
	bx lr

leds_set_5_left:
	ldr r0, =LEDR
	ldr r1, =led_5_left
	ldr r2, [r1]
	str r2, [r0]
	bx lr

leds_set_5_right:
	ldr r0, =LEDR
	ldr r1, =led_5_right
	ldr r2, [r1]
	str r2, [r0]
	bx lr

/*
 *	Test if character is a whitespace, if so, adjust index location
 */
is_whitespace:
    @ Input: r0 - index
    @ Output: r0 - int (1 if whitespace, 0 if not)

    ldrb r8, [r3, r0] 			// input[idx]
	cmp r8, #32					// Compare character with ASCII value 32 (space)
    moveq r0, #1				// If equal, move 1 into r0
    movne r0, #0				// If not equal, move 0 into r0
    bx lr

/*
 *	Test if character is between two ASCII table values
 */
in_range:
	@ Input: r0 - index
	@ Input: r1 - lower range
	@ Input: r2 - upper range
	@ Input: r3 - input
	@ Output: r1 - int (1 if in range, 0 if not)

    ldrb r8, [r3, r0] 			// input[idx]
	cmp r8, r1
	blt _return_out_of_range	// Less than lower range

	cmp r8, r2
	bgt _return_out_of_range	// Greater than upper range

	b _return_in_range

_return_out_of_range:
	mov r1, #0
	b _end_in_range
_return_in_range:
	mov r1, #1
_end_in_range:
	bx lr

/*
 *	Test if character is valid. Change any uppercase characters to lower case
 */
is_valid:
    @ Input: r0 - index
    @ Output: r0 - int (1 if valid, 0 if not)

	push {r14}					// Save LR from main

	/* Check if input[r0] is a digit */
	mov r1, #48					// ASCII 0
	mov r2, #57					// ASCII 9
	bl in_range
	cmp r1, #1
	beq _return_valid

	/* Check if input[r0] is a lowcase letter */
	mov r1, #97					// ASCII a
	mov r2, #122				// ASCII z
	bl in_range
	cmp r1, #1
	beq _return_valid

	/* Check if input[r0] is uppercase, convert to lower if it is */
	mov r1, #65					// ASCII A
	mov r2, #90					// ASCII Z
	bl in_range
	cmp r1, #1
	beq _convert_case

	b _return_invalid			// If we made it this far, character must be invalid

_convert_case:
	ldrb r8, [r3, r0]			// input[idx]
	add r8, r8, #32				// Convert upper to lower (+32)
	strb r8, [r3, r0]
_return_valid:
	mov r0, #1
	b _end_is_valid
_return_invalid:
	mov r0, #0
_end_is_valid:
	pop {r15}					// Return back to main

/*
 *	Start execution
 */
_start:
	@ Function return / arg 1: r0
	@ Function return / arg 2: r1
	@ Function argument 3: r2
	@ Input array: r3

	@ Input length: r4
	@ Half of input length: r5
	@ Forward index: r6
	@ Reverse Index: r7
	@ Variables local to function: r8, r9

	bl leds_clear				// Clear LEDs to start
	ldr r3, =input				// Initialize input variable
	mov r4, #0					// Initialize length variable

_find_length:
    ldrb r0, [r3, r4]			// Load byte offset by length

    cmp r0, #0					// check for null-terminator
    beq _start_check			// begin checking for palindrome once null-terminator found

    add r4, r4, #1				// increment length
    b _find_length				// continue until end-of-string

_start_check:
	cmp r4, #1
	ble _err_too_short			// Output error if length is less than 2

	lsr r5, r4, #1 				// half the length of our input
	mov r6, #0					// forward index variable
	sub r7, r4, #1				// reverse index variable (length-1)

_loop:
	/* If halfway through the input has been reached without
	 * failing to match, we have a winner!
	 */
	cmp r6, r5
	bgt _is_palindrome

	/* Check front half of input using forward index */
	mov r0, r6					// pass fwd idx as arg to function
	bl is_whitespace			// test if input[fwd idx] is a whitespace
	cmp r0, #1
	addeq r6, r6, #1			// is whitespace, increment fwd idnx

	/* check back half of input using reverse index */
	mov r0, r7
	bl is_whitespace			// test if input[rev idx] is a whitespace
	cmp r0, #1
	subeq r7, r7, #1			// is whitespace, decrement rev indx

	/* Check if input[fwd indx] is invalid, correct for letter case */
	mov r0, r6
	bl is_valid
	cmp r0, #1
	bne _err_invalid_char

	/* Check if input[rev indx] is invalid, correct for letter case */
	mov r0, r7
	bl is_valid
	cmp r0, #1
	bne _err_invalid_char

	/* Check that indecies are the same */
	ldrb r8, [r3, r6]			// input[fwd idx]
	ldrb r9, [r3, r7]			// input[rev idx]
	cmp r8, r9
	bne _is_not_palindrome

	/* Update indicies, loop back */
	add r6, r6, #1
	sub r7, r7, #1
	b _loop

_err_invalid_char:
	/* print 'Error: invalid character' */
	b _exit
_err_too_short:
	/* print 'Error: input too short' */
	b _exit
_is_palindrome:
	/* print 'Palindrome detected' */
	bl leds_set_5_right
	b _exit
_is_not_palindrome:
	/* print 'Not a palindrome' */
	bl leds_set_5_left
	b _exit
_exit:
	// Branch here for exit
	/* Check if counter is less than 2, if so, no LEDs & error msg on UART */
	/* Check if illegal characters, if so, no LEDs & error msg on UART */
	b .

.data
.align
	led_5_left:		.word	0x3e0
	led_5_right:	.word	0x1f
	input: 			.asciz	"Gag"
.end
