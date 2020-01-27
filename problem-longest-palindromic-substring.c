#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "longest-palindromic-substring.h"

struct test_data
{
  char *input;
  char *expected;
};

struct test_data tests_set[] = 
{
  {"aabb", "aa"},
  {"aba", "aba"}
};

void exec_tests(struct test_data *tests, int n)
{
    for (int i=0; i<n; ++i)
    {
        char *result =longestPalindrome(tests[i].input);

        if (strcmp(result, tests[i].expected) == 0)
        {
            printf("PASS %s\n", result);
        } else {
            printf("FAILED! %s\n", tests[i].input);
            printf(" R %s\n", result);
            printf(" E %s\n", tests[i].expected);
        }

        free(result);
    }

}

int main(int argc, char *argv[])
{
    printf("Longest palindromic substring\n");

    exec_tests(tests_set, sizeof(tests_set)/ sizeof(tests_set[0]));

    return 0;
}
