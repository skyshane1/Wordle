#include <stdlib.h>
#include <ncurses.h>
#include <stdbool.h>
#include "help.h"

WINDOW *HELP;

void help(){
	initscr();
	noecho();
	cbreak();

	if ((LINES < 24) || (COLS < 80)) {
		endwin();
		puts("Your terminal needs to be at least 80x24");
		exit(2);
	}

	start_color();
	/* print welcome text */

	clear();

	mvprintw(0, (COLS / 2) - 4, "CWORDLE");
	refresh();
	create_help();
	mvprintw(4, (COLS / 2) - 6, "HOW TO PLAY");
	mvprintw(6, (COLS / 2) - 38, "Guess the WORDLE in six tries.");
	mvprintw(8, (COLS / 2) - 38, "Each guess must be a valid five-letter word. Hit the enter button to submit.");
	mvprintw(10, (COLS / 2) - 38, "After each guess, the color of the tiles will change to show how close your");
	mvprintw(11, (COLS / 2) - 38, "guess was to the word. Green means the letter is in the correct spot, yellow");
	mvprintw(12, (COLS / 2) - 38, "means the letter is in the word but not in the correct spot, and red means");
	mvprintw(13, (COLS / 2) - 38, "the letter is not in the word.");
	mvprintw(15, (COLS / 2) - 38, "Use the arrow keys and enter to navigate the menu and q to escape unless");
	mvprintw(16, (COLS / 2) - 38, "otherwise noted.");
	mvprintw(18, (COLS / 2) - 38, "Have fun!");

	int key;
	do{
		key = getch();

	}while(key != 'q');
	destroy_help();
	clear();
	endwin();
}

void create_help()
{
	HELP = newwin(H_HEIGHT, H_WIDTH, 5,(COLS/2) - (H_WIDTH/2));
	draw_help();
}

void draw_help()
{
	box(HELP, 0, 0);
	wrefresh(HELP);
}

void destroy_help()
{
	wborder(HELP, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
	wrefresh(HELP);

	delwin(HELP);
}
