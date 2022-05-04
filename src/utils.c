#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

int max(int a, int b)
{
    return (a > b) ? a : b;
}

char *read_fasta(char *filename)
{
    // Open file
    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Error opening file: %s\n", filename);
        return NULL;
    }

    // Allocate buffers
    int seq_len = 0;
    char *seq = (char *)malloc(sizeof(char) * (seq_len + 1));
    seq[0] = '\0';
    char *buffer = (char *)malloc(sizeof(char) * 81);

    // Read file contents into buffer
    size_t len = 0;
    ssize_t read;
    while ((read = getline(&buffer, &len, fp)) != -1)
    {
        // Ignore line if begins with '>'
        if (buffer[0] == '>')
            continue;
        seq = realloc(seq, sizeof(char) * (seq_len + len));
        // Remove '\n'
        buffer[read - 1] = '\0';
        strcat(seq, buffer);
        seq_len += read;
    }

    // Close file
    fclose(fp);

    return seq;
}