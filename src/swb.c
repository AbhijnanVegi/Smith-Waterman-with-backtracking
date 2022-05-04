#include <stdio.h>

#include "swb.h"
#include "utils.h"

int score(char a, char b)
{
    // Score = +3 if match, -3 if mismatch
    if (a == b)
        return MATCH_SCORE;
    else
        return -MATCH_SCORE;
}

void smith_waterman(int l1, int l2, char *s1, char *s2)
{
    printf("\nAligning Input sequences\n");

    // Initialize the scoring matrix
    int matrix[l1 + 1][l2 + 1];
    for (int i = 0; i <= l1; i++)
    {
        matrix[i][0] = 0;
    }
    for (int j = 0; j <= l2; j++)
    {
        matrix[0][j] = 0;
    }

    // Fill the scoring matrix
    for (int i = 1; i <= l1; i++)
    {
        for (int j = 1; j <= l2; j++)
        {
            int match = matrix[i - 1][j - 1] + score(s1[i - 1], s2[j - 1]);
            int delete = matrix[i - 1][j] - GAP_PENALTY;
            int insert = matrix[i][j - 1] - GAP_PENALTY;
            matrix[i][j] = max(match, max(delete, insert));
        }
    }

    // Print the scoring matrix
    printf("\nScoring Matrix\n");
    print_mat(l1, l2, (int*)matrix);
}