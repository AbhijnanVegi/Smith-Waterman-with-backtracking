#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "swb.h"

int main(int argc, char *argv[])
{
    char *s1, *s2;

    printf("Smith Waterman with Backtracking\n");
    printf("---------------------------------\n");

    printf("Enter the first string: ");
    s1 = (char *)malloc(sizeof(char) * 100);
    scanf("%s", s1);

    printf("Enter the second string: ");
    s2 = (char *)malloc(sizeof(char) * 100);
    scanf("%s", s2);

    // Run alignment algorithm
    smith_waterman(strlen(s1), strlen(s2), s1, s2);

    return 0;
}