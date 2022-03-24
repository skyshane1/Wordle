#include <stdlib.h>
#include <ncurses.h>
#include <stdbool.h>
#include "game.h"

WINDOW *BOARD[30];

void game()
{
	char key;
	char word[6] = {'h', 'e', 'l', 'l', 'o', '\0'};
	char guess[6] = {' ', ' ', ' ', ' ', ' ', '\0'};
	int sq;
	int col = 0;
	int row = 0;
	int entered = 0;
	bool win = false;

	/* initialize curses */

	initscr();
	noecho();
	cbreak();

	if ((LINES < 24) || (COLS < 80)) {
		endwin();
		puts("Your terminal needs to be at least 80x24");
		exit(2);
	}

	start_color();
	init_pair(CORRECT_PAIR, COLOR_GREEN, COLOR_GREEN);
	init_pair(PARTIAL_PAIR, COLOR_YELLOW, COLOR_YELLOW);

	/* print welcome text */

	clear();

	mvprintw(0, (COLS / 2) - 4, "CWORDLE");
	refresh();


	/* draw board */

	create_board();

	do {
		key = getch();
		if(key == 10 && entered == 5){
			col = 0;
			win = check_word(word, guess, row, col);
			row++;
			entered = 0;
		} else if(key == 127 && entered > 0){
			col--;
			mvprintw((row * 5) + 3, ((COLS/2) - (SQ_WIDTH * 2.5)) + ((9 * col) + 4), " ");
			guess[entered] = ' ';
			entered--;
		} else if(entered < 5 && row < 6 && (122 >= key && key >= 97)){
			mvprintw((row * 5) + 3, ((COLS/2) - (SQ_WIDTH * 2.5)) + ((9 * col) + 4), "%c", key);
			col++;
			guess[entered] = key;
			entered++;
		}
		if(win == true){
			mvprintw(1 + (6 * SQ_HEIGHT), (COLS/2) - 5, "You win!!");
			mvprintw(2 + (6 * SQ_HEIGHT), (COLS/2) - 9, "Press 1 to quit!");
			row = 6;
			entered = -1;
		}

	} while (key != 49);
	destroy_board();
	clear();
	endwin();
}

bool check_word(char word[6], char guess[6], int row, int col){
	int gy = 0;
	int correct = 0;
	int dup[5]={0,0,0,0,0};
	for(int k = 0; k < 5; k++){
		for(int p = 0; p < 5; p++){
			if(word[p]==word[k])
				dup[k]=dup[k]+1;
		}
	}
	for(int i = 0; i < 5; i++){
		gy = 0;
		for(int j = 0; j < 5; j++){
			if(i == j && word[j] == guess[i]){
				dup[j]=dup[j]-1;
				gy = 2;
		} else if ((word[j] == guess[i] && gy != 2) && dup[j]>0){
				gy = 1;
			}
		}
		if(gy == 2){
			attron(COLOR_PAIR(CORRECT_PAIR));
			for(int i = 0; i < 3; i++){
				mvhline((row * 5)+2+ i, (COLS/2 - (SQ_WIDTH*2.5)) + ((9 * col) + 1),CORRECT, 7);
			}
			attroff(COLOR_PAIR(CORRECT_PAIR));
			mvprintw((row * 5) + 3, ((COLS/2) - (SQ_WIDTH * 2.5)) + ((9 * col) + 4), "%c", guess[i]);
			col++;
			correct++;
		} else if (gy == 1){
			attron(COLOR_PAIR(PARTIAL_PAIR));
			for(int i = 0; i < 3; i++){
				mvhline((row * 5)+2+ i, (COLS/2 - (SQ_WIDTH*2.5)) + ((9 * col) + 1),PARTIAL, 7);
			}
			attroff(COLOR_PAIR(PARTIAL_PAIR));
			mvprintw((row * 5) + 3, ((COLS/2) - (SQ_WIDTH * 2.5)) + ((9 * col) + 4), "%c", guess[i]);
			col++;
		} else {
			col++;
		}	
	}
	if(correct == 5){
		return true;
	} else {
		return false;
	}
}

void create_board(void)
{
	int i;
	int starty, startx;
	int center = (COLS/2) - (SQ_WIDTH * 2.5);

	starty = 1;
	for (i = 0; i < 5; i++) {
		startx = (i * SQ_WIDTH) + center;
		BOARD[i] = newwin(SQ_HEIGHT, SQ_WIDTH, starty,startx);
	}

	starty = 1 + SQ_HEIGHT;
	for (i = 5; i < 10; i++) {
		startx = ((9 - i) * SQ_WIDTH) + center;
		BOARD[i] = newwin(SQ_HEIGHT, SQ_WIDTH, starty,startx);
	}

	starty = 1 + (2 * SQ_HEIGHT);
	for (i = 10; i < 15; i++) {
		startx = ((i - 10) * SQ_WIDTH) + center;
		BOARD[i] = newwin(SQ_HEIGHT, SQ_WIDTH, starty,startx);
	}
	starty = 1 + (3 * SQ_HEIGHT);
	for (i = 15; i < 20; i++) {
		startx = ((19 - i) * SQ_WIDTH) + center;
		BOARD[i] = newwin(SQ_HEIGHT, SQ_WIDTH, starty,startx);
	}

	starty = 1 + (4 * SQ_HEIGHT);
	for (i = 20; i < 25; i++) {
		startx = ((i - 20) * SQ_WIDTH) + center;
		BOARD[i] = newwin(SQ_HEIGHT, SQ_WIDTH, starty,startx);
	}

	starty = 1 + (5 * SQ_HEIGHT);
	for (i = 25; i < 30; i++) {
		startx = ((29 - i) * SQ_WIDTH) + center;
		BOARD[i] = newwin(SQ_HEIGHT, SQ_WIDTH, starty,startx);
	}


	/* put border on each window and refresh */

	for (i = 0; i < 30; i++) {
		draw_square(i);
	}
}

void destroy_board(void)
{

	/* erase every box and delete each window */

	for (int i = 0; i < 30; i++) {
		wborder(BOARD[i], ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
		wrefresh(BOARD[i]);

		delwin(BOARD[i]);
	}
}

void draw_square(int sq)
{
	box(BOARD[sq], 0, 0);

	wrefresh(BOARD[sq]);
}

