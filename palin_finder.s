.global _start

/*
 *	Test if character is a whitespace, if so, adjust index location
 */
is_whitespace:
    @ Input: r0 - index
    @ Output: r0 - int (1 if whitespace, 0 if not)

    ldrb r5, [r1, r0] 	// input[idx]
	cmp r5, #32			// Compare character with ASCII value 32 (space)
    moveq r0, #1		// If equal, move 1 into r0
    movne r0, #0		// If not equal, move 0 into r0
    bx lr

/*
 *	Test if character is between two ASCII table values
 */
in_range:
	@ Input: r0 - index
	@ Input: r2 - lower range
	@ Input: r3 - upper range
	@ Output: r0 - int (1 if in range, 0 if not)

    ldrb r5, [r1, r0] 	// input[idx]
	cmp r5, r2
	blt _return_out_of_range

	cmp r5, r3
	bgt _return_out_of_range

	b _return_in_range

_return_out_of_range:
	mov r0, #0
	b _end_in_range
_return_in_range:
	mov r0, #1
_end_in_range:
	bx lr

/*
 *	Test if character is valid. Change any uppercase characters to lower case
 */
is_valid:
    @ Input: r0 - index
    @ Output: r0 - int (1 if valid, 0 if not)

	mov r5, r0		// Tmp var for indx

	/* Check if input[r0] is a digit */
	mov r2, #48
	mov r3, #57
	bl in_range
	cmp r0, #1
	beq _return_valid

	/* Check if input[r0] is a lowcase letter */
	mov r2, #97
	mov r3, #122
	bl in_range
	cmp r0, #1
	beq _return_valid

	/* Check if input[r0] is uppercase, convert to lower if it is */
	mov r2, #65
	mov r3, #90
	bl in_range
	cmp r0, #1
	ldrbeq r5, [r1, r5]
	subeq r5, r5, #32
	strbeq r5, [r1, r5]
	beq _return_valid

	b _return_invalid			// If we made it this far, character must be invalid

_return_valid:
	mov r0, #1
	b _end_is_valid
_return_invalid:
	mov r0, #0
_end_is_valid:
	bx lr

/*
 *	Start execution
 */
_start:
	@ Function return / arg: r0
	@ Input array: r1
	@ Function argument 2: r3
	@ Function argument 3: r4

	@ Variable local to function: r4
	@ Input length: r5
	@ Half of input length: r6
	@ Forward index: r7
	@ Reverse Index: r8

	ldr r1, =input		// Initialize input variable
	mov r5, #0			// Initialize length variable

_find_length:
    ldrb r0, [r1, r5]	// Load byte offset by length

    cmp r0, #0			// check for null-terminator
    beq _start_check	// begin checking for palindrome once null-terminator found

    add r5, r5, #1		// increment length
    b _find_length		// continue until end-of-string

_start_check:
	cmp r5, #1
	ble _err_too_short	// Output error if length is less than 2

	lsr r6, r5, #1 		// half the length of our input
	mov r7, #0			// forward index variable
	sub r8, r5, #1		// reverse index variable

_loop:
	/* If halfway through the input has been reached without
	 * failing to match, we have a winner!
	 */
	cmp r7, r6
	bgt _is_palindrome

	/* Check front half of input using forward index */
	mov r0, r7			// pass fwd indx as arg to function
	bl is_whitespace	// test if input[fwd idx] is a whitespace
	cmp r0, #1
	addeq r7, r7, #1	// is whitespace, increment fwd idnx

	/* check back half of input using reverse index */
	mov r0, r8
	bl is_whitespace	// test if input[rev idx] is a whitespace
	cmp r0, #1
	subeq r8, r8, #1	// is whitespace, decrement rev indx

	/* Check if input[fwd indx] is invalid, correct for letter case */
	mov r0, r7
	bl is_valid
	cmp r0, #1
	bne _err_invalid_char

	/* Check if input[rev indx] is invalid, correct for letter case */
	mov r0, r8
	bl is_valid
	cmp r0, #1
	bne _err_invalid_char

	add r7, r7, #1
	sub r8, r8, #1
	b _loop

_err_invalid_char:
	/* print 'Error: invalid character' */
	b _exit
_err_too_short:
	/* print 'Error: input too short' */
	b _exit
_is_palindrome:
	/* print 'Palindrome detected' */
	/* light 5 RIGHT most LEDs */
	b _exit
_is_not_palindrome:
	/* print 'Not a palindrome' */
	/* light 5 LEFT most LEDs */
	b _exit
_exit:
	// Branch here for exit
	/* Check if counter is less than 2, if so, no LEDs & error msg on UART */
	/* Check if illegal characters, if so, no LEDs & error msg on UART */
	b .

.data
.align
	// This is the input you are supposed to check for a palindrom
	// You can modify the string during development, however you
	// are not allowed to change the name 'input'!
	input: .asciz "Grav ned den varg"
.end
