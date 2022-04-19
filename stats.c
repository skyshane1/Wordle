#include <stdlib.h>
#include <ncurses.h>
#include <stdbool.h>
#include "stats.h"

WINDOW *STATS;

void stats(){
	FILE *fin = fopen("stats_data.txt", "r");
        if(fin == NULL){
                 printf("File not found!");
		 exit(-1);
         }
	 int win, played, streak, mstreak=0;
	 double stotal, sbiggest;
	 double scores[6];
         fscanf(fin, "%d", &win);
	 fscanf(fin, "%d", &played);
	 fscanf(fin, "%d", &streak);
	 fscanf(fin, "%d", &mstreak);
  	 for(int i=0; i<6; i++)
             fscanf(fin, "%lf", &scores[i]);      
        fclose(fin);
      
	stotal = 0;
	initscr();
	noecho();
	cbreak();

	if ((LINES < 24) || (COLS < 80)) {
		endwin();
		puts("Your terminal needs to be at least 80x24");
		exit(2);
	}

	start_color();
	init_pair(GRAPH_PAIR, COLOR_GREEN, COLOR_GREEN);
	/* print welcome text */

	clear();

	for(int i = 0; i < 6; i++){
		stotal += scores[i];
		if(sbiggest < scores[i]){
			sbiggest = scores[i];
		}
	}

	sbiggest = ((sbiggest/stotal)* 100) / 38;
	
	mvprintw(0, (COLS / 2) - 4, "CWORDLE");
	refresh();
	create_stats();
	mvprintw(4, (COLS / 2) - 3, "STATS");
	mvprintw(6, (COLS / 2) - 21, "Played: %d Win %: %d Streak: %d Max Streak: %d", played, win, streak, mstreak);
	for(int i = 0; i < 6; i++){
		double temp = ((scores[i]/stotal) * 100) / sbiggest;
		int tempp = temp;
		mvprintw(8+(i*2), (COLS / 2) - 21, "%d", i+1);
		attron(COLOR_PAIR(GRAPH_PAIR));
		mvhline(8+(i*2),(COLS/2) - 19, GRAPH, tempp + 1);
		attroff(COLOR_PAIR(GRAPH_PAIR));
		mvprintw(8+(i*2), ((COLS / 2) - 21) + tempp + 3, " %.0f", scores[i]);
	}

	int key;
	do{
		key = getch();

	}while(key != 'q');
	destroy_stats();
	clear();
	endwin();
}

void create_stats()
{
	STATS = newwin(ST_HEIGHT, ST_WIDTH, 5,(COLS/2) - (ST_WIDTH/2));
	draw_stats();
}

void draw_stats()
{
	box(STATS, 0, 0);
	wrefresh(STATS);
}

void destroy_stats()
{
	wborder(STATS, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
	wrefresh(STATS);

	delwin(STATS);
}
