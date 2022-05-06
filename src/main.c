#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "swb.h"
#include "utils.h"

char s1[(int)1e8];
char s2[(int)1e8];

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Usage: %s <path to file> <path to file>\n", argv[0]);
        exit(1);
    }

    printf("Smith Waterman with Backtracking\n");
    printf("---------------------------------\n");

    read_fasta(argv[1], s1);
    read_fasta(argv[2], s2);

    // Run alignment algorithm
    smith_waterman(strlen(s1), strlen(s2), s1, s2);

    return 0;
}