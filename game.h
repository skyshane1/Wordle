#include <stdlib.h>
#include <ncurses.h>
#include <stdbool.h>
#include "BST.h"

#define SQ_HEIGHT 5
#define SQ_WIDTH 9

#define CORRECT '@'
#define PARTIAL '#'
#define INCORRECT '$'

#define CORRECT_PAIR 1
#define PARTIAL_PAIR 2
#define INCORRECT_PAIR 3

void game(int flag, char s[5], BST *p);
void create_board(void);
void destroy_everything(void);
void create_keys(void);
void draw_square(int sq);
void draw_keys(int ks);
bool check_word(char word[6], char guess[6], int row, int col);

