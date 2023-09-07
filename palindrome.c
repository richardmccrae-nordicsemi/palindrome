/**
 * @file palidrome.c

 * @author Richard McCrae (https://github.com/richardmccrae-nordicsemi)
 * @brief
 * @version 0.1
 * @date 2023-09-03
 *
 * @copyright Copyright (c) 2023
 *
 */

/**
 * @brief Determine if a user input is a palindrome or not.
 *
 * A palindrome reads the same backwards as forwards.
 *
 * Constraints
 *  Case insensitive
 *  alphanumeric and spaces are accepted, but spaces are ignored
 *  no punctuation or special characters
 *  Input must be atleast two characters
 *
 */

#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define ASCII_WHITESPACE      32
#define ASCII_NUMBER_LOW      48
#define ASCII_NUMBER_HIGH     57
#define ASCII_UPPERCASE_LOW   65
#define ASCII_UPPERCASE_HIGH  90
#define ASCII_LOWERCASE_LOW   97
#define ASCII_LOWERCASE_HIGH  122
#define ASCII_CASE_CORRECT    32

char is_valid_char(char *c, int idx)
{
    char tmp = c[idx];

    if (c == NULL) {
        return -1;
    }

    /* Check for illegal characters, left */
    if (tmp >= ASCII_NUMBER_LOW && tmp <= ASCII_NUMBER_HIGH) {
        // pass
    } else if (tmp >= ASCII_LOWERCASE_LOW && tmp <= ASCII_LOWERCASE_HIGH) {
        // pass
    } else if (tmp >= ASCII_UPPERCASE_LOW && tmp <= ASCII_UPPERCASE_HIGH) {
        tmp = tmp + ASCII_CASE_CORRECT;
        c[idx] = tmp;
    } else {
        // illegal character
        return 0;
    }

    return 1;
}

int is_whitespace(char c)
{
    if (c == ASCII_WHITESPACE) {
        return 1;
    } else {
        return 0;
    }
}

/**
 * @brief Check if user's input string is a palindrome.
 * Disregard spaces
 *
 * @param input User input string
 * @return int 0 is not a palidrome, 1 if it is
 */
int is_palindrome(char input[])
{
    uint8_t l, r;
    int i, j;
    int half_len;
    int length = 0;

check_len:
    if (input[length] != '\0') {
        length = length + 1;
        goto check_len;
    } else {
        if (length < 2) {
            goto error_too_short;
        }
    }

    half_len = length / 2;
    i = 0;
    j = length-1;

    // printf("Length: %d, half: %d\n", length, half_len);

loop:
    // for(i = 0, j = length-1; i <= half_len; ++i, --j)
    // {
    if (i > half_len) {
        goto end_palindrome;
    }

    /* Ignore whitespaces */
    if (is_whitespace(input[i])) {
        i = i + 1;
    }
    if (is_whitespace(input[j])) {
        j = j -1;
    }

    // printf("input[%d]: %c, input[%d]: %c\n", i, input[i], j, input[j]);
    if (!is_valid_char(input, i)) {
        goto error_invalid_character;
    }
    if (!is_valid_char(input, j)) {
        goto error_invalid_character;
    }

    if (input[i] == input[j]) {
        i++;
        j--;
        goto loop;
    } else {
        // Not a palindrome
        goto end_not_palindrome;
    }

error_invalid_character:
    printf("Error: Invalid character\n");
    goto end_error;
error_too_short:
    printf("Error: Entry must be atleast 2 characters\n");
    goto end_error;

end_palindrome:
    printf("A palindrome\n");
    return 1;
end_not_palindrome:
    printf("Not a palindrome\n");
    return 0;
end_error:
    return -1;
}
