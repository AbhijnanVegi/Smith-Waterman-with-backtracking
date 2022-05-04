#ifndef SMITH_WATERMAN_H
#define SMITH_WATERMAN_H

#define GAP_PENALTY 2
#define MATCH_SCORE 3

int score(char a, char b);

void smith_waterman(int l1, int l2, char *s1, char *s2);

#endif