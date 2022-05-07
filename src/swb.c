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

int chunk_swb(int i, int j, int p, int q, Score (*matrix)[l2 + 1], char *s1, char *s2)
{
    int maxScore = 0;
    int start = (i - 1)*p - 1;
    for(int x = start; x < start + p; x++)
    {
        int start2 = (j - 1)*q - 1;
        for(int y = j; y < start2 + q; y++)
        {
            int match = matrix[x - 1][y - 1].score + score(s1[x - 1], s2[y - 1]);
            int delete = matrix[x - 1][y].score - GAP_PENALTY;
            int insert = matrix[x][y - 1].score - GAP_PENALTY;

            setScore(&matrix[x][y], x, y,
                     max(match, max(delete, insert)),
                     (match >= max(delete, insert)) ? DIAGONAL : (delete >= insert) ? HORIZONTAL
                                                                                    : VERTICAL);

            // checking if this is the highest score so far
            if (matrix[x][y].score > maxScore)
            {
                maxScore = matrix[x][y].score;
            }
        }
    }
    // printf("MaxScore: %d\n", maxScore);
    return maxScore;
}

int chunkwise_swb(int p, int q, int l1, int l2, Score (*matrix)[l2 + 1],char *s1, char *s2)
{
    //get bigger and smaller of p and q
    // int major = p > q ? p : q;
    // int minor = p > q ? q : p;
    int maxScore = 0;
    for(int sum = 2; sum <= l1+l2; sum++)
    {
        for(int i = 1; i <= sum - 1; i++)
        {
            int j = sum - i;
            if(i > l1 || j > l2)
            {
                continue;
            }
            else
            {
                int score = chunk_swb(i, j, p, q, matrix, s1, s2);
                if (score > maxScore)
                {
                    maxScore = score;
                }
            }
        }
    }
    // printf("maxScore: %d\n", maxScore);
    return maxScore;
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
#elif ADIAG

    if (l1 > l2)
    {
        char *temp = s1;
        s1 = s2;
        s2 = temp;
        int temp_l = l1;
        l1 = l2;
        l2 = temp_l;
    }

    int maxScore = 0;
    int *prev2 = (int *)calloc(max(l1 + 1, l2 + 1), sizeof(int));
    int *prev1 = (int *)calloc(max(l1 + 1, l2 + 1), sizeof(int));
    int *curr = (int *)calloc(max(l1 + 1, l2 + 1), sizeof(int));

    tick(&t);
    for (int i = 0; i < l1 + l2 - 1; i++)
    {
        // Number of diagonal cells
        int diags;
        if (i + 1 <= min(l1, l2))
            diags = i + 1;
        else if (i + 1 > min(l1, l2) && i + 1 <= max(l1, l2))
            diags = min(l1, l2);
        else
            diags = l1 + l2 - i - 1;

        if (i + 1 < min(l1, l2))
        {
#pragma omp parallel for
            for (int j = 0; j < diags; j++)
            {
                int match = prev2[j] + score(s1[i - j], s2[j]);
                int delete = prev1[j] - GAP_PENALTY;
                int insert = prev1[j + 1] - GAP_PENALTY;

                curr[j + 1] = max(match, max(delete, insert));
                if (curr[j + 1] > maxScore)
                {
                    maxScore = curr[j + 1];
                }
            }
        }
        else if (i + 1 == min(l1, l2))
        {
#pragma omp parallel for
            for (int j = 0; j < diags; j++)
            {
                int match = prev2[j] + score(s1[i - j], s2[j]);
                int delete = prev1[j] - GAP_PENALTY;
                int insert = prev1[j + 1] - GAP_PENALTY;

                curr[j] = max(match, max(delete, insert));
                if (curr[j] > maxScore)
                {
                    maxScore = curr[j];
                }
            }
        }
        else
        {
#pragma omp parallel for
            for (int j = 0; j < diags; j++)
            {
                int match = prev2[j + 1] + score(s1[l1 - j - 1], s2[i - l1 + j + 1]);
                int delete = prev1[j] - GAP_PENALTY;
                int insert = prev1[j + 1] - GAP_PENALTY;

                curr[j] = max(match, max(delete, insert));
                if (curr[j] > maxScore)
                {
                    maxScore = curr[j];
                }
            }
        }

        // for (int j = 0; j <= diags; j++)
        // {
        //     printf("%d ", curr[j]);
        // }
        // printf("\n");

        int *t = prev2;
        prev2 = prev1;
        prev1 = curr;
        curr = t;
    }
    double time = tock(&t);

    printf("\nScore: %d\n", maxScore);
    printf("Time taken : %lf ms\n", time);
#elif CHUNKY    
    Score(*matrix)[l2 + 1] = (Score(*)[l2 + 1]) malloc(sizeof(Score) * (l1 + 1) * (l2 + 1));

    // Initializing Score pointer that points to the max score
    
    for (int i = 0; i <= l1; i++)
    {
        matrix[i][0].score = 0;
    }
    for (int j = 0; j <= l2; j++)
    {
        matrix[0][j].score = 0;
    }
    print_mat(l1, l2, (Score *)matrix);
    tick(&t);
    int maxScore = chunkwise_swb(1, 1, l1, l2, matrix, s1, s2);
    double time = tock(&t);
    printf("\nScoring Matrix\n");
    print_mat(l1, l2, (Score *)matrix);
    printf("\nScore: %d\n", maxScore);
    printf("Time taken : %lf ms\n", time);

// void recursive_swb(int i, int j)
// {
// }
#endif
}