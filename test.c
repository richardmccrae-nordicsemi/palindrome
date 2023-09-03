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

void test_is_number(void)
{
    ret = is_number('0');
    TEST_ASSERT_TRUE(ret);

    ret = is_number('9');
    TEST_ASSERT_TRUE(ret);
}

void test_is_not_number(void)
{
    char character = 'a';

    ret = is_number(character);
    TEST_ASSERT_FALSE(ret);

    ret = is_number('+');
    TEST_ASSERT_FALSE(ret);
}

void test_is_lowercase(void)
{
    ret = is_lowercase('a');
    TEST_ASSERT_TRUE(ret);

    ret = is_lowercase('z');
    TEST_ASSERT_TRUE(ret);
}

void test_is_not_lowercase(void)
{
    ret = is_lowercase('A');
    TEST_ASSERT_FALSE(ret);

    ret = is_lowercase('4');
    TEST_ASSERT_FALSE(ret);

    ret = is_lowercase('!');
    TEST_ASSERT_FALSE(ret);
}

void test_is_uppercase(void)
{
    ret = is_uppercase('A');
    TEST_ASSERT_TRUE(ret);

    ret = is_uppercase('Z');
    TEST_ASSERT_TRUE(ret);
}

void test_is_not_uppercase(void)
{
    ret = is_uppercase('a');
    TEST_ASSERT_FALSE(ret);

    ret = is_uppercase('4');
    TEST_ASSERT_FALSE(ret);

    ret = is_uppercase('!');
    TEST_ASSERT_FALSE(ret);
}

void test_convert_lower_to_uppercase(void)
{
    char a = convert_lower_to_uppercase('a');
    TEST_ASSERT_EQUAL_CHAR('A', a);

    a = convert_lower_to_uppercase('z');
    TEST_ASSERT_EQUAL_CHAR('Z', a);
}


/**  Mid-level  **/
void test_is_valid_char_valid(void)
{
    ret = is_valid_char('a');
    TEST_ASSERT_TRUE(ret);

    ret = is_valid_char('z');
    TEST_ASSERT_TRUE(ret);

    ret = is_valid_char('A');
    TEST_ASSERT_TRUE(ret);

    ret = is_valid_char('Z');
    TEST_ASSERT_TRUE(ret);

    ret = is_valid_char('0');
    TEST_ASSERT_TRUE(ret);

    ret = is_valid_char('9');
    TEST_ASSERT_TRUE(ret);
}

void test_is_valid_char_invalid(void)
{
    ret = is_valid_char('!');
    TEST_ASSERT_FALSE(ret);

    ret = is_valid_char('-');
    TEST_ASSERT_FALSE(ret);

    ret = is_valid_char('?');
    TEST_ASSERT_FALSE(ret);
}
/**  Palinedrome  **/
void test_palindrome_no_spaces_even(void)
{
    char * user_input = "fedcbaabcdef";

    ret = is_palindrome(user_input, strlen(user_input));
    TEST_ASSERT_TRUE(ret);
}

void test_palindrome_no_spaces_odd(void)
{
    char * user_input = "fedcba1abcdef";

    ret = is_palindrome(user_input, strlen(user_input));
    TEST_ASSERT_TRUE(ret);
}

void test_palindrome_spaces_even(void)
{
    char * user_input = "fed cbaabcdef";

    ret = is_palindrome(user_input, strlen(user_input));
    TEST_ASSERT_TRUE(ret);
}

void test_palindrome_spaces_odd(void)
{
    char * user_input = "fedcba1abc def";

    ret = is_palindrome(user_input, strlen(user_input));
    TEST_ASSERT_TRUE(ret);
}

void test_palindrome_case_insensitive(void)
{
    char * user_input = "FEDCBA321123abcdef";

    ret = is_palindrome(user_input, strlen(user_input));
    TEST_ASSERT_TRUE(ret);
}

/**    Not a palindrome    **/
void test_no_palindrome_even(void)
{
    char * user_input = "fedczbaabqcdef";

    ret = is_palindrome(user_input, strlen(user_input));
    TEST_ASSERT_FALSE(ret);
}

void test_no_palindrome_odd(void)
{
    char * user_input = "fedcba1abcdef9";

    ret = is_palindrome(user_input, strlen(user_input));
    TEST_ASSERT_FALSE(ret);
}

void test_illegal_characters_even(void)
{
    char * user_input = "ab;;ba";

    ret = is_palindrome(user_input, strlen(user_input));
    TEST_ASSERT_EQUAL_INT(-1, ret);
}

void test_illegal_characters_odd(void)
{
    char * user_input = "abc!cba";

    ret = is_palindrome(user_input, strlen(user_input));
    TEST_ASSERT_EQUAL_INT(-1, ret);
}

/**     Test main      **/
int main(void)
{
    UNITY_BEGIN();

    /* low-level fxs */
    RUN_TEST(test_is_whitespace);
    RUN_TEST(test_is_not_whitespace);
    RUN_TEST(test_is_number);
    RUN_TEST(test_is_not_number);
    RUN_TEST(test_is_lowercase);
    RUN_TEST(test_is_not_lowercase);
    RUN_TEST(test_is_uppercase);
    RUN_TEST(test_is_not_uppercase);
    RUN_TEST(test_convert_lower_to_uppercase);

    /* mid-level */
    RUN_TEST(test_is_valid_char_valid);
    RUN_TEST(test_is_valid_char_invalid);

    /* Palindrome */
    RUN_TEST(test_palindrome_no_spaces_even);
    RUN_TEST(test_palindrome_no_spaces_odd);
    RUN_TEST(test_palindrome_spaces_even);
    RUN_TEST(test_palindrome_spaces_odd);
    RUN_TEST(test_palindrome_case_insensitive);

    /* Not a palindrome */
    RUN_TEST(test_no_palindrome_even);
    RUN_TEST(test_no_palindrome_odd);
    RUN_TEST(test_illegal_characters_even);
    RUN_TEST(test_illegal_characters_odd);

    return UNITY_END();
}
