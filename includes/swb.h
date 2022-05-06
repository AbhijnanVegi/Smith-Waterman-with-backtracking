#ifndef SMITH_WATERMAN_H
#define SMITH_WATERMAN_H

#define GAP_PENALTY 2
#define MATCH_SCORE 3

typedef struct Score {
    int x,y,score, direction;
} Score;

typedef enum Direction {
    DIAGONAL,
    HORIZONTAL,
    VERTICAL
} Direction;

int score(char a, char b);

void smith_waterman(char *s1, char *s2);
void print_mat(int l1, int l2, Score *mat);


#endif