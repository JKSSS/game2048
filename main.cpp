#include <iostream>
#include <vector>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <curses.h>

using namespace std;

void initialize()
{
	//ncurses
	initscr();

	//
	cbreak();
	
	//
	noecho();

	//
	curs_set(0);

	//
	srand(time(NULL));
}

void shutdown()
{
	endwin();
}


int main()
{
	initialize();

	char ch = 'n';

	do{
		move(5,5);
		addch(ch);
		mvprintw(2, 2, "jks");
		ch = getch();
	
	}while(ch != 'Q' && ch != 'q');

	shutdown();
	return 0;
}
