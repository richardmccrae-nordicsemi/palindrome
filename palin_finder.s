.global _start


// Please keep the _start method and the input strings name ("input") as
// specified below
// For the rest, you are free to add and remove functions as you like,
// just make sure your code is clear, concise and well documented.

loop:
	/* Load single byte of user input */
	ldrb r1, [r0]

	/* Check if r1 is null, end-of-string */
	cmp r1, #0
	beq _exit

	/* Operate */

	/* Increment r1 to next character (byte) of input, increment counter */
	add r1, r1, #1
	add r2, r2, #1

	/* */

	/* Loop */
	b loop

check_input:
	/* Initialize byte counter to determine length of user input */
	mov r2, #0

find_length:
    /* Load the next character from the string into R0 */
    ldrb R0, [R1, R2]

    /* Check if R0 is null (end of string) */
    cmp R0, #0
    beq start_check

    /* Increment the counter */
    add R2, R2, #1

    /* Loop to find length */
    b find_length

check_palindrom:
	// Here you could check whether input is a palindrom or not


is_palindrom:
	// Switch on only the 5 leftmost LEDs
	// Write 'Palindrom detected' to UART


is_no_palindrom:
	// Switch on only the 5 rightmost LEDs
	// Write 'Not a palindrom' to UART

_start:
	// Here your execution starts
	ldr r0, =input
	bl check_input
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
