#include <stdlib.h>
#include <ncurses.h>
#include <stdbool.h>
#include "game.h"

void create_menu();
void draw_option(int sq);
void draw_menu();

int HEIGHT = 5;
int WIDTH = 18;

WINDOW *MENU[5];

int main(int argc, char **argv){
	int key;
	int option = 0;
	initscr();
	noecho();
	cbreak();
	if ((LINES < 24) || (COLS < 80)) {
		endwin();
		puts("Your terminal needs to be at least 80x24");
		exit(2);
	}
	clear();

	mvprintw(0, (COLS / 2) - 4, "CWORDLE");
	refresh();

	create_menu();
	do {
		key = getch();
		switch (key) {
			case 65: //up
				if(option > 0){
					option--;
				}
				break;
			case 66: //down
				if(option < 5){
					option++;
				}
				break;
			case 10: //enter
				if(option == 0){
					game();
					draw_menu();
				}
		}
		mvprintw(0,0,"option: %d", option);
		mvprintw(1,0,"press: %d", key);	
	} while (key != 'q');
	endwin();
}

void create_menu()
{
	int starty;
	int center = (COLS/2) - (WIDTH/2);

	for(int i = 0; i < 5; i++){
		starty = 1 + (i*HEIGHT);
		MENU[i] = newwin(HEIGHT, WIDTH, starty, center);
	}
	draw_menu();
}

void draw_menu()
{
	for(int i = 0; i < 5; i++){
		draw_option(i);
		mvprintw((i * 5) + 3, (COLS/2) - (3), "DAILY");
	}
}

void draw_option(int sq)
{
	box(MENU[sq], 0, 0);
	wrefresh(MENU[sq]);
}
