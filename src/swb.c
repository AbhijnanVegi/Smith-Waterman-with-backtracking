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

void smith_waterman(int l1, int l2, char *s1, char *s2)
{
    printf("\nAligning Input sequences\n");

    // Initialize the scoring matrix
    // int matrix[l1 + 1][l2 + 1];
    Score matrix[l1 + 1][l2 + 1], maxScore;
    
    setScore(&maxScore, 0, 0, 0, 0);
     
    for (int i = 0; i <= l1; i++)
    {
        matrix[i][0].score = 0;
    }
    for (int j = 0; j <= l2; j++)
    {
        matrix[0][j].score = 0;
    }

    // Fill the scoring matrix
    for (int i = 1; i <= l1; i++)
    {
        for (int j = 1; j <= l2; j++)
        {
            int match = matrix[i - 1][j - 1].score + score(s1[i - 1], s2[j - 1]);
            int delete = matrix[i - 1][j].score - GAP_PENALTY;
            int insert = matrix[i][j - 1].score - GAP_PENALTY;

            setScore(&matrix[i][j], i, j, 
                    max(match, max(delete, insert)), 
                    (match >= max(delete, insert)) ? DIAGONAL : (delete >= insert) ? HORIZONTAL : VERTICAL);

            // checking if this is the highest score so far
            if (matrix[i][j].score > maxScore.score)
            {
                setScore(&maxScore, i, j, matrix[i][j].score, 0);
            }
        }
    }

    // Print the scoring matrix
    printf("\nScoring Matrix\n");
    print_mat(l1, l2, (Score*)matrix);

    // Printing the scoring matrix with the directions
    printf("\nTraceback\n");
    int x = maxScore.x;
    int y = maxScore.y;
    while (matrix[x][y].score != 0)
    {
        printf("(%d,%d) -> ", x+1, y+1);
        char c1 = s1[x - 1];
        char c2 = s2[y - 1];
        switch (matrix[x][y].direction)
        {
            case DIAGONAL:
                x--;
                y--;
                break;
            case HORIZONTAL:
                x--;
                c2 = '-';
                break;
            case VERTICAL:
                y--;
                c1 = '-';
                break;
        }
        printf("%c %c\n", c1, c2);
    }
}