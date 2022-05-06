#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "swb.h"
#include "utils.h"
#include "helper.h"

// Global variables
Score *matrix;
int l1, l2;

int score(char a, char b)
{
    // Score = +3 if match, -3 if mismatch
    if (a == b)
        return MATCH_SCORE;
    else
        return -MATCH_SCORE;
}

void print_mat(int l1, int l2, Score *mat)
{
    for (int i = 0; i <= l1; i++)
    {
        for (int j = 0; j <= l2; j++)
        {
            printf("%3d ", mat[i * (l2 + 1) + j].score);
        }
        printf("\n");
    }
}

// sets all variables inside a struct var
void setScore(Score *v, int x, int y, int score, int dir)
{
    v->x = x;
    v->y = y;
    v->score = score;
    v->direction = dir;
}

void traceback(Score (*matrix)[l2 + 1], Score *maxScore, char *s1, char *s2)
{

    for (int x = maxScore->x, y = maxScore->y; matrix[x][y].score != 0;)
    {
        printf("(%d,%d) -> ", x + 1, y + 1);
        char c1 = s1[x - 1];
        char c2 = s2[y - 1];
        if (matrix[x][y].direction == DIAGONAL)
        {
            x--;
            y--;
        }
        else if (matrix[x][y].direction == HORIZONTAL)
        {
            x--;
            c2 = '-';
        }
        else
        {
            y--;
            c1 = '-';
        }
        printf("%c %c\n", c1, c2);
    }
}

void recursive_swb(int i, int j)
{
}

void smith_waterman(char *s1, char *s2)
{
    timer t;
    printf("\nAligning Input sequences\n");
    l1 = strlen(s1);
    l2 = strlen(s2);

    // Fill the scoring matrix
#ifdef BASELINE
    // Initialize the scoring matrix
    Score(*matrix)[l2 + 1] = (Score(*)[l2 + 1]) malloc(sizeof(Score) * (l1 + 1) * (l2 + 1));

    // Initializing Score pointer that points to the max score
    Score *maxScore = &matrix[0][0];

    for (int i = 0; i <= l1; i++)
    {
        matrix[i][0].score = 0;
    }
    for (int j = 0; j <= l2; j++)
    {
        matrix[0][j].score = 0;
    }
    tick(&t);
    for (int i = 1; i <= l1; i++)
    {
        for (int j = 1; j <= l2; j++)
        {
            int match = matrix[i - 1][j - 1].score + score(s1[i - 1], s2[j - 1]);
            int delete = matrix[i - 1][j].score - GAP_PENALTY;
            int insert = matrix[i][j - 1].score - GAP_PENALTY;

            setScore(&matrix[i][j], i, j,
                     max(match, max(delete, insert)),
                     (match >= max(delete, insert)) ? DIAGONAL : (delete >= insert) ? HORIZONTAL
                                                                                    : VERTICAL);

            // checking if this is the highest score so far
            if (matrix[i][j].score > maxScore->score)
            {
                maxScore = &matrix[i][j];
            }
        }
    }
    double time = tock(&t);
    printf("\nScoring Matrix\n");
    print_mat(l1, l2, (Score *)matrix);
    // Printing the scoring matrix with the directions
    printf("\nTraceback\n");
    traceback(matrix, maxScore, s1, s2);
    printf("\nScore: %d\n", maxScore->score);
    printf("Time taken: %lf\n", time);
#elif LINEAR
    int maxScore = 0;

    int *top = (int *)calloc(l2 + 1, sizeof(int));
    for (int i = 0; i <= l2; i++)
    {
        top[i] = 0;
    }
    int *curr = (int *)malloc(sizeof(int) * (l2 + 1));
    curr[0] = 0;
    tick(&t);
    for (int i = 1; i <= l1; i++)
    {
        for (int j = 1; j <= l2; j++)
        {
            int match = top[j - 1] + score(s1[i - 1], s2[j - 1]);
            int delete = top[j] - GAP_PENALTY;
            int insert = curr[j - 1] - GAP_PENALTY;

            curr[j] = max(match, max(delete, insert));
            if (curr[j] > maxScore)
            {
                maxScore = curr[j];
            }
        }
        int *t = top;
        top = curr;
        curr = t;
        curr[0] = 0;
    }
    double time = tock(&t);
    printf("\nScore: %d\n", maxScore);
    printf("Time taken : %lf ms\n", time);
#endif

    // Print the scoring matrix
}