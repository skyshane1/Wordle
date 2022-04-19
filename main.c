/**
 * some code, specifically the ncurses menu game UX, borrowed and modified from https://www.linuxjournal.com/content/programming-text-windows-ncurses
 */

#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <stdbool.h>
#include "game.h"
#include "stats.h"
#include "help.h"
#include "BST.h"

void create_menu();
void draw_option(int sq);
void draw_menu();

int HEIGHT = 5;
int WIDTH = 18;

WINDOW *MENU[5];

int main(int argc, char **argv){
	BST *guesses = create_bst();
	char **computer_words = malloc (sizeof(char *) * 2315);
	int key;
	int option = 0;

	FILE *guessfile = fopen("guesses", "r");
	char temp[6];
	while(fscanf(guessfile, "%s", temp) != EOF){
		bst_insert(guesses, temp);
	}
	fclose(guessfile);
	for(int i = 0; i < 2315; i++){
		computer_words[i] = malloc(sizeof(char) * 6);
	}
	int index = 0;
	FILE *allowedfile = fopen("allowed.txt", "r");
	while(fscanf(guessfile, "%s", temp) != EOF){
		strcpy(computer_words[index], temp);
		index++;
	}
	srand(time(NULL));
	int num = rand() % 2314;


	initscr();
	noecho();
	cbreak();
	if ((LINES < 24) || (COLS < 80)) {
		endwin();
		puts("Your terminal needs to be at least 80x24");
		exit(2);
	}
	clear();
	start_color();
	mvprintw(0, (COLS / 2) - 4, "CWORDLE");
	refresh();
	mvprintw((option*HEIGHT) + 1 + HEIGHT/2, (COLS / 2 - 11), ">");
	create_menu();

	mvprintw(40,40,"test %s %d", computer_words[num], num);
	do {
		key = getch();
		mvprintw((option*HEIGHT) + 1 + HEIGHT/2, (COLS / 2 - 11), " ");
		switch (key) {
			case 65: //up
				if(option > 0){
					option--;
				}
				break;
			case 66: //down
				if(option < 4){
					option++;
				}
				break;
			case 10: //enter
				if(option == 0){
					game(0, "cocoa", guesses);
					mvprintw(0, (COLS / 2) - 4, "CWORDLE");
					refresh();
					create_menu();
				}else if(option == 1){
					game(1, "plane", guesses);
					mvprintw(0, (COLS / 2) - 4, "CWORDLE");
					refresh();
					create_menu();
				}else if(option == 2){
					stats();
					mvprintw(0, (COLS / 2) - 4, "CWORDLE");
					refresh();
					create_menu();
				}else if(option == 3){
					help();
					mvprintw(0, (COLS / 2) - 4, "CWORDLE");
					refresh();
					create_menu();
				}
		}
		mvprintw((option*HEIGHT) +1+ HEIGHT/2, (COLS / 2 - 11), ">");
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
		switch (i){
			case 0:
				mvprintw((i * 5) + 3, (COLS/2) - (3), "PLAY!");
				break;
			case 1:
				mvprintw((i * 5) + 3, (COLS/2) - (4), "PRACTICE");
				break;
			case 2:
				mvprintw((i * 5) + 3, (COLS/2) - (3), "STATS");
				break;
			case 3:
				mvprintw((i * 5) + 3, (COLS/2) - (6), "INSTRUCTIONS");
				break;
			case 4:
				mvprintw((i * 5) + 3, (COLS/2) - (4), "SETTINGS");
				break;
		}
	}
}

void draw_option(int sq)
{
	box(MENU[sq], 0, 0);
	wrefresh(MENU[sq]);
}
