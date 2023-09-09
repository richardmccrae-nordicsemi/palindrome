/**
 * @file palindrome.h
 * @author Richard McCrae (https://github.com/richardmccrae-nordicsemi)
 * @brief
 * @version 0.1
 * @date 2023-09-03
 *
 * @copyright Copyright (c) 2023
 *
 */

int is_palindrome(char *input);
int is_whitespace(char c);
int is_valid_char(char *c, int idx);

/* Longest substring */
char* longestPalindrome(char* s);
int expandAroundCenter(char* s, int len, int left, int right);
int preprocess(char* s, char* preprocessed);
int substr_example(void);
