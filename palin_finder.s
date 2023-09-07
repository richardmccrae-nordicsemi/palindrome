.global _start


// Please keep the _start method and the input strings name ("input") as
// specified below
// For the rest, you are free to add and remove functions as you like,
// just make sure your code is clear, concise and well documented.

test_whitespace:
	mov r5, [r0, r2] ; get input[index]
	cmp r5, #32	; 32 is ASCII value for whitespace
	bnq _is_not_whitespace
	add r2, r2, #1	; Increment index by one, aka ignore whitespace

_is_not_whitespace:
	/* pass */
	bx lr

_start:
	// Here your execution starts
	ldr r0, =input
	mov r1, #0	; r1 will be the length

_find_length:
    ldrb r2, [r0, r1]	; Load byte offset by length into r2

    /* Check if r2 is null (end of string) */
    cmp r2, #0
    beq start_check

    add r1, r1, #1	; increment length
    b _find_length	; continue until end of string is found

_start_check:
	/* Raise error is length is less than 2 */
	cmp r1, #1
	ble _err_too_short

	/* Initialize local variables */
	mov r6, #0	; forward index variable
	mov r7, r1	; reverse index variable
	lsr r8, r1, #1 ; half of r1 (length)

	/*
		r0: input
		r1: length
		r2: function arg 1
		r3: function arg 2

		r6: forward index
		r7: reverse index
		r8: half-length

	*/

_loop:
	/*
		If halfway through the input has been reached without
		failing to match, we have a winner!
	*/
	cmp r6, r8	;
	bgt _is_palindrome

	/* Check and account for possible whitespaces */
	mov r2, r6
	bl test_whitespace	; test if input[fwd idx] is a whitespace
	mov r6, r2 ; Update fwd index

	mov r2, r7	; check back half of input, starting from final character
	bl test_whitespace	; test if input[rev idx] is a whitespace
	mov r7, r2 ; Update rev index

	/* Verify that characters are valid, correct for letter case */


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
