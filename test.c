/**
 * @file test.c
 * @author Richard McCrae (https://github.com/richardmccrae-nordicsemi)
 * @brief
 * @version 0.1
 * @date 2023-09-03
 *
 * @copyright Copyright (c) 2023
 *
 * Test suite for palindrome.c
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unity.h>
#include "palindrome.h"

void setUp(void) { /* Do setup here like memory allocation, etc. */ }
void tearDown(void) { /* Do teardown here like memory deallocation, etc. */ }

int ret;

/**  low-level fxs  **/
void test_is_whitespace(void)
{
    ret = is_whitespace(' ');
    TEST_ASSERT_TRUE(ret);
}

void test_is_not_whitespace(void)
{
    ret = is_whitespace('a');
    TEST_ASSERT_FALSE(ret);
}

void test_is_valid_char_valid(void)
{
    char lower[] = "abc";
    char upper_A[] = "A";
    char upper_Z[] = "Z";
    char number_0[] = "0";
    char number_9[] = "9";

    ret = is_valid_char(lower,0);
    TEST_ASSERT_EQUAL_INT(1, ret);
    TEST_ASSERT_EQUAL_CHAR('a', lower[0]);

    ret = is_valid_char(upper_A,0);
    TEST_ASSERT_EQUAL_INT(1, ret);
    TEST_ASSERT_EQUAL_CHAR('a', upper_A[0]);

    ret = is_valid_char(upper_Z,0);
    TEST_ASSERT_EQUAL_INT(1, ret);
    TEST_ASSERT_EQUAL_CHAR('z', upper_Z[0]);

    ret = is_valid_char(number_0,0);
    TEST_ASSERT_EQUAL_INT(1, ret);
    TEST_ASSERT_EQUAL_CHAR('0', number_0[0]);

    ret = is_valid_char(number_9,0);
    TEST_ASSERT_EQUAL_INT(1, ret);
    TEST_ASSERT_EQUAL_CHAR('9', number_9[0]);
}

void test_is_valid_char_invalid(void)
{
    char invalid[] = "!";
    ret = is_valid_char(invalid,0);
    TEST_ASSERT_FALSE(ret);

    // ret = is_valid_char(NULL,0);
    // TEST_ASSERT_EQUAL_INT(-1, ret);
}


/**  Palinedrome  **/
void test_palindrome_no_spaces_even(void)
{
    ret = is_palindrome("fedcbaabcdef");
    TEST_ASSERT_EQUAL_INT(1, ret);
}

void test_palindrome_no_spaces_odd(void)
{
    ret = is_palindrome("fedcba1abcdef");
    TEST_ASSERT_EQUAL_INT(1, ret);
}

void test_palindrome_spaces_even(void)
{
    ret = is_palindrome("fed cbaabcdef");
    TEST_ASSERT_EQUAL_INT(1, ret);
}

void test_palindrome_spaces_odd(void)
{
    ret = is_palindrome("fedcba1abc def");
    TEST_ASSERT_EQUAL_INT(1, ret);
}

void test_palindrome_case_insensitive(void)
{
    char arr[] = "FEDCBA321123abcdef";
    ret = is_palindrome(arr);
    TEST_ASSERT_EQUAL_INT(1, ret);
}

void test_palindrome_many_spaces(void)
{
    char arr[] = "3                 21    12         3";
    ret = is_palindrome(arr);
    TEST_ASSERT_EQUAL_INT(1, ret);
}

/**    Not a palindrome    **/
void test_no_palindrome_even(void)
{
    ret = is_palindrome("fedczbaabqcdef");
    TEST_ASSERT_EQUAL_INT(0, ret);
}

void test_no_palindrome_odd(void)
{
    ret = is_palindrome("fedcba1abcdef9");
    TEST_ASSERT_EQUAL_INT(0,ret);
}

void test_illegal_characters_even(void)
{
    ret = is_palindrome("ab;;ba");
    TEST_ASSERT_EQUAL_INT(-1, ret);
}

void test_illegal_characters_odd(void)
{
    ret = is_palindrome("abc!cba");
    TEST_ASSERT_EQUAL_INT(-1, ret);
}

void test_illegal_one_character(void)
{
    ret = is_palindrome("a");
    TEST_ASSERT_EQUAL_INT(-1, ret);
}

/**    Longest substring, palindrome exists    **/
void test_substr_positive(void)
{
    char s[] = "Abba CC  dccA";
    char output[16] = {0};
    char preprocessed[strlen(s) + 1];

    preprocess(s, preprocessed);

    strcpy(output, longestPalindrome(preprocessed));
    TEST_ASSERT_EQUAL_STRING("accdcca", output);
}

void test_substr_negative(void)
{
    char s[] = "abcdefghij";
    char output[16] = {0};
    char preprocessed[strlen(s) + 1];

    preprocess(s, preprocessed);

    strcpy(output, longestPalindrome(preprocessed));
    TEST_ASSERT_EQUAL_STRING("", output);
}

/**     Test main      **/
int main(void)
{
    UNITY_BEGIN();

    /* low-level fxs */
    // RUN_TEST(test_is_whitespace);
    // RUN_TEST(test_is_not_whitespace);
    // RUN_TEST(test_is_valid_char_valid);
    // RUN_TEST(test_is_valid_char_invalid);

    /* Palindrome */
    // RUN_TEST(test_palindrome_no_spaces_even);
    // RUN_TEST(test_palindrome_no_spaces_odd);
    // RUN_TEST(test_palindrome_spaces_even);
    // RUN_TEST(test_palindrome_spaces_odd);
    // RUN_TEST(test_palindrome_case_insensitive);
    // RUN_TEST(test_palindrome_many_spaces);

    /* Not a palindrome */
    // RUN_TEST(test_no_palindrome_even);
    // RUN_TEST(test_no_palindrome_odd);
    // RUN_TEST(test_illegal_characters_even);
    // RUN_TEST(test_illegal_characters_odd);
    // RUN_TEST(test_illegal_one_character);

/**    Longest substring, palindrome exists    **/
    RUN_TEST(test_substr_positive);
    RUN_TEST(test_substr_negative);

    return UNITY_END();
}
