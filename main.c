/**
 * @file main.c
 * @author Richard McCrae (https://github.com/richardmccrae-nordicsemi)
 * @brief Take user input string as program argument, check if it is a palidrome
 * @version 0.1
 * @date 2023-09-03
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "palindrome.h"

int main(int argc, char *argv[])
{
    int res;

    /* No string passed as argument to program */
    if (argc != 2) {
        printf("Invalid argument");
        return -1;
    }

    res = is_palindrome(argv[1]);

    if (res){
        printf("Palidrome\n");
    } else {
        printf("Nope\n");
    }

    return 0;
}
