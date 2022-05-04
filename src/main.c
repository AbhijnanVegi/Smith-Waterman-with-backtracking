#include <stdio.h>
#include <stdlib.h>

#include "helper.h"

int main(int argc, char *argv[])
{
    timer t;

    char *s1, *s2;

    printf("Smith Waterman with Backtracking\n");
    printf("---------------------------------\n");

    printf("Enter the first string: ");
    s1 = (char *)malloc(sizeof(char) * 100);
    scanf("%s", s1);

    printf("Enter the second string: ");
    s2 = (char *)malloc(sizeof(char) * 100);
    scanf("%s", s2);

    //TODO Run the Smith-Waterman algorithm 

    return 0;
}