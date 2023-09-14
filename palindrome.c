/**
 * @file palidrome.c

 * @author Richard McCrae (https://github.com/richard-jh-mccrae)
 * @brief
 *
 * Determine if a user input is a palindrome or not.
 *
 *  Constraints:
 *  	Input must be atleast two characters long.
 *		Only valid characters are [0-9A-Za-z] and white space
 *		Whitespaces are to be ignored
 *
 *		A palindrome is to deisply on JTAG UART, "Palindrome detected"
 *			whlie lighting the five right most red LEDs
 *		Not a palindrome is to display just that, whlie lighting the
 *			five left most red LEDs
 *		Invalid user entry shall provide an error message
 *
 * @date 2023-09-03
 *
 */

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

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
    if (input[length] == '\0') {
        if (length < 2) {
            goto error_too_short;
        }
    } else {
        length = length + 1;
        goto check_len;
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
        goto loop;
    }
    if (is_whitespace(input[j])) {
        j = j -1;
        goto loop;
    }

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

int preprocess(char* s, char* preprocessed) {
    int index = 0;
    for (int i = 0; i < strlen(s); ++i) {
        if (s[i] >= '0' && s[i] <= '9') {
            preprocessed[index++] = s[i];
        } else if (s[i] >= 'A' && s[i] <= 'Z') {
            preprocessed[index++] = tolower(s[i]);
        } else if (s[i] >= 'a' && s[i] <= 'z') {
            preprocessed[index++] = s[i];
        } else if (s[i] != ' ') {
            return -1;
        }
    }
    preprocessed[index] = '\0';
    return 0;
}

int expandAroundCenter(char* s, int len, int left, int right) {
    while (left >= 0 && right < len && s[left] == s[right]) {
        left--;
        right++;
    }
    return right - left - 1;
}

char* longestPalindrome(char* s) {
    int i;
    int len, len1, len2;
    int start = 0, end = 0;
    int lenMax = 0;

    len = strlen(s);
    if (len < 2) {
        return s;
    }

    for (i = 0; i < len; i++) {
        len1 = expandAroundCenter(s, len, i, i);
        len2 = expandAroundCenter(s, len, i, i + 1);
        lenMax = len1 > len2 ? len1 : len2;

        if (lenMax > end - start) {
            start = i - (lenMax - 1) / 2;
            end = i + lenMax / 2;
        }
    }

    if (end - start < 1) { // Check if the longest palindrome found has less than 2 characters
        s[0] = '\0';  // Return an empty string if no valid palindrome found
        return s;
    }

    s[end + 1] = '\0';
    return s + start;
}

int substr_example(void) {
    char s[] = "Abba CC dccA";
    char preprocessed[strlen(s) + 1];

    if (preprocess(s, preprocessed) == -1) {
        printf("Error: Invalid characters in input.\n");
        return -1;
    }

    printf("%s\n", longestPalindrome(preprocessed));

    return 0;
}
