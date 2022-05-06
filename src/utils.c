#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

int max(int a, int b)
{
    return (a > b) ? a : b;
}

int read_fasta(char *filename, char *seq)
{
    // Open file
    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Error opening file: %s\n", filename);
        return 0;
    }

    // Allocate buffers
    int seq_len = 0;

    // Read file contents into buffer
    char c;
    while ((c = getc(fp)) != EOF)
    {
        if (c == '>')
        {
            // Skip the rest of the line
            while ((c = getc(fp)) != '\n')
                ;
        }
        else if (c != '\n')
        {
            seq[seq_len++] = c;
        }
    }

    // Close file
    return seq_len;
}