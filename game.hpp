#include <ncurses.h>

#define N 4
#define WIDTH 5

#define Status_FAILED	0
#define Status_WIN    	1
#define Status_NORNAL	2
#define Status_QUIT		3
class Game{
public :
	Game(){
		initArray();
	}

	void draw();
	void processInput();
	int Status;

private:
	void initArray();
	int data[N][N];
	void drawItem(int row, int col, char ch);
	void drawNum(int row, int col, int num);
};

void Game::processInput()
{
	char ch ;
	ch = getch();
	if(ch == 'Q' || ch == 'q')
		Status = Status_QUIT;
	else
		Status = (Status+ 1)%3;
}

void Game::initArray()
{
	for(int i=0; i<N; ++i)
		for(int j=0; j<N; ++j)
			data[i][j] = 1024;
}

void Game::draw()
{
	clear();
	for(int i =0; i<=N; ++i)
	{
		for(int j=0; j<=N; ++j)
		{
			//相交点
			drawItem(i*2, 1+j*WIDTH, '+');
			//竖线
			if(i!=N)
				drawItem(i*2+1, 1+j*WIDTH, '|');
			//横线
			if(j!=N)
			{
				for(int k =1; k< WIDTH; ++k)
					drawItem(i*2, 1+j*WIDTH+k, '-');
			}
			if(i!=N && j!= N)
				drawNum(i*2+1, (j+1)*WIDTH , data[i][j]);

	
		}
	}
	
	if(Status == Status_WIN)
		mvprintw(2*N+1, 0, "YOU WIN, PREES R TO CONTINUE");
	else if(Status == Status_FAILED)
		mvprintw(2*N+1, 0, "YOU FAILED, PRESS R  TO CONTINUE");
}

void Game::drawItem(int row, int col, char ch)
{
	move(row, col);
	addch(ch);
}

void Game::drawNum(int row, int col, int num)
{
	while(num > 0)
	{
		drawItem(row, col, num%10 + '0');
		num /= 10;
		--col;
	}

	//drawItem(row, col, (num) + '0');

}
