#ifndef UTILS_H
#define UTILS_H

#define max(a,b) ((a) > (b) ? (a) : (b))
#define min(a,b) ((a) < (b) ? (a) : (b))

int read_fasta(char *filename, char* seq);

#endif