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


int is_whitespace(char c)
{
    if (c == ASCII_WHITESPACE) {
        return 1;
    } else {
        return 0;
    }
}

int is_number(char c)
{
    if (c >= ASCII_NUMBER_LOW && c <= ASCII_NUMBER_HIGH) {
        return 1;
    } else {
        return 0;
    }
}

int is_lowercase(char c)
{
    if (c >= ASCII_LOWERCASE_LOW && c <= ASCII_LOWERCASE_HIGH) {
        return 1;
    } else {
        return 0;
    }
}

int is_uppercase(char c)
{
    if (c >= ASCII_UPPERCASE_LOW && c <= ASCII_UPPERCASE_HIGH) {
        return 1;
    } else {
        return 0;
    }
}

char convert_lower_to_uppercase(char c)
{
    c = c - ASCII_CASE_CORRECT;
}

char is_valid_char(char c)
{
    /* Check for illegal characters, left */
    if (is_number(c)) {
        // pass
    } else if (is_uppercase(c)) {
        // pass
    } else if (is_lowercase(c)) {
        c = convert_lower_to_uppercase(c);
    } else {
        // illegal character
        return 0;
    }

    return c;
}
/**
 * @brief Check if user's input string is a palindrome.
 * Disregard spaces
 *
 * @param input User input string
 * @return int 0 is not a palidrome, 1 if it is
 */
int is_palindrome(const char *input, int input_strlen)
{
    uint8_t l, r;
    int i, j;
    int half_len = input_strlen/2;

    if (strlen(input) < 2 || input_strlen < 2) {
        return -1;
    }

    for(i = 0, j = input_strlen-1; i <= half_len; ++i, --j)
    {
        /* Ignore whitespaces */
        if (is_whitespace(input[i])) {
            i++;
        }
        if (is_whitespace(input[j])) {
            j--;
        }

        l = is_valid_char(input[i]);
        if (!l) {
            return -1;
        }
        r = is_valid_char(input[j]);
        if (!r) {
            return -1;
        }

        if (l == r) {
            // pass
        } else {
            // Not a palindrome
            return 0;
        }
    }

    return 1;
}
