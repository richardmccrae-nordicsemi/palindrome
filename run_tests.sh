if [ -e "test" ]; then
    rm test
fi
gcc -o test test.c palindrome.c /usr/local/src/unity.c -I/.
./test
