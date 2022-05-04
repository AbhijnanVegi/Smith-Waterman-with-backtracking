#include <stdio.h>

#include "utils.h"

int max(int a , int b)
{
    return (a > b) ? a : b;
}


void print_mat(int l1, int l2, int *mat)
{
    for (int i = 0; i <= l1; i++)
    {
        for (int j = 0; j <= l2; j++)
        {
            printf("%3d ", mat[i * (l2 + 1) + j]);
        }
        printf("\n");
    }
}