#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
extern int x[9][9];
extern int y[9][9];
extern int z[9][9];
extern int current[9][9];
extern int sw[96];
void write_sudoku();
void print_hanisudoku(const char* filename,int* known);
void hanidoku();
