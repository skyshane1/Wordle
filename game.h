#include <stdlib.h>
#include <ncurses.h>
#include <stdbool.h>

#define SQ_HEIGHT 5
#define SQ_WIDTH 9

#define CORRECT '@'
#define PARTIAL '#'

#define CORRECT_PAIR 1
#define PARTIAL_PAIR 2
void game(void);
void create_board(void);
void destroy_board(void);

void draw_square(int sq);
bool check_word(char word[6], char guess[6], int row, int col);

