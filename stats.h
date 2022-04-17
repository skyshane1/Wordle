#include <stdlib.h>
#include <ncurses.h>
#include <stdbool.h>

#define ST_HEIGHT 15
#define ST_WIDTH 50

#define GRAPH '@'

#define GRAPH_PAIR 1

void stats(void);
void create_stats(void);
void draw_stats(void);
void destroy_stats(void);
