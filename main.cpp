#include <iostream>
#include <vector>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <curses.h>
#include "game.hpp"

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
	Game game;
//	char ch = 'n';

	do{
	//	move(5,5);
	//	addch(ch);
	//	mvprintw(2, 2, "jks");
	//	ch = getch();
	
		game.draw();
		game.processInput();
		//ch = getch();


	}while(game.getStatus() != Status_QUIT);

	shutdown();
	return 0;
}
