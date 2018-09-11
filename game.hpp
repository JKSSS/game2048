#include <ncurses.h>
#include <vector>

using namespace std;


#define N 4
#define WIDTH 5
#define TARGET 256

#define Status_FAILED	0
#define Status_WIN    	1
#define Status_NORNAL	2
#define Status_QUIT		3

class Game{
public :
	Game(){
//		initArray();
		restart();
	}

	void draw();
	void processInput();
//	int Status;
	int getStatus() {return Status; }

private:
	void initArray();
	void drawItem(int row, int col, char ch);
	void drawNum(int row, int col, int num);
	void restart();
	bool randNew();

	bool moveLeft();
	bool moveRight();
	bool moveUp();
	bool moveDown();

	bool isDead();
	bool isWin();
	bool change(int before[N][N], int after[N][N]);
private: 
	int data[N][N];
	int Status;
};

bool Game::change(int before[N][N], int after[N][N])
{
	for(int i=0; i<N; i++)
		for(int j=0; j<N; j++)
			if(before[i][j]!= after[i][j])
				return true;
	return false;
}

bool Game::isWin()
{
	for(int i =0; i<N; i++)
		for(int j=0; j<N; j++)
			if(data[i][j] == TARGET)
				return true;
	return false;
}

bool Game::isDead()
{
	for(int i =0; i<N; i++)
		for(int j=0; j<N; j++)
		{
			if((j+1<N) &&( (data[i][j] * data[i][j+1] == 0) || data[i][j] == data[i][j+1]))
				return false;
			if((i+1<N) && ((data[i][j] * data[i+1][j] == 0) || data[i][j] == data[i+1][j]))
				return false;
		}

	return true;
}


bool Game::moveUp()
{
	int tmp[N][N];
	
	for(int j =0; j<N; ++j)
	{
		int writePos = 0;
		int lastNum =0;
		for(int i=0; i<N; ++i)
		{
			tmp[i][j] = data[i][j];
			if(data[i][j] == 0)
				continue;
			
			if(lastNum == 0)
				lastNum = data[i][j];
			else
			{
				if(lastNum == data[i][j])
				{
					data[writePos][j] = lastNum*2;
					lastNum = 0;
				}
				else
				{
					data[writePos][j] = lastNum;
					lastNum = data[i][j];
				}
				++writePos;
			}
			data[i][j] = 0;
		}
		if(lastNum != 0)
			data[writePos][j] = lastNum;	
	}
	return change(tmp, data);

}

bool Game::moveDown()
{
	int tmp[N][N];
	for(int j=0; j<N; ++j)
	{
		int writePos = N-1;
		int lastNum = 0;
		for(int i=N-1; i>=0; --i)
		{
			tmp[i][j] = data[i][j];
			if(data[i][j] == 0)
				continue;

			if(lastNum == 0)
				lastNum = data[i][j];
			else
			{
				if(lastNum == data[i][j])
				{
					data[writePos][j] = lastNum*2;
					lastNum = 0;
				}
				else
				{
					data[writePos][j] = lastNum;
					lastNum = data[i][j];
				}
				--writePos;
			}
			data[i][j] = 0;
		}
		if(lastNum != 0)
			data[writePos][j] = lastNum;
	}
	return change(tmp, data);
}

bool Game::moveRight()
{
	int tmp[N][N];
	for(int i= 0; i<N; ++i)
	{
		int writePos = N-1;
		int lastNum = 0;
		for(int j =N-1; j>=0; --j)
		{
			tmp[i][j] = data[i][j];
			if(data[i][j] == 0)
				continue;
			
			if(lastNum == 0)
				lastNum = data[i][j];
			else
			{
				if(lastNum == data[i][j])
				{
					data[i][writePos] = lastNum*2;
					lastNum = 0;
				}
				else
				{
					data[i][writePos] = lastNum;
					lastNum = data[i][j];
				}
				--writePos;
			}
			data[i][j] = 0;
		}
		if(lastNum != 0)
			data[i][writePos] = lastNum;
	}
	return change(tmp, data);
}


bool Game::moveLeft()
{
	int tmp[N][N];
	for(int i=0; i<N;i++)
	{
		int writePos = 0;
		int lastNum =0;
		for(int j =0; j<N; ++j)
		{
			tmp[i][j] = data[i][j];
			if(data[i][j] == 0)
				continue;

			if(lastNum == 0)
				lastNum = data[i][j];
			else
			{
				if(lastNum == data[i][j])
				{
					data[i][writePos] = lastNum*2;
					lastNum = 0;
				}
				else
				{
					data[i][writePos] = lastNum;
					lastNum = data[i][j];					
				}
				++writePos;
			}
			data[i][j] = 0;
		}
		if(lastNum != 0)
			data[i][writePos] = lastNum;
	}
	return change(tmp,data);
}


bool Game::randNew()
{
	vector<int> emptyPos;
	for(int i=0; i<N; ++i)
		for(int j=0; j<N; ++j)
		{
			if(data[i][j] == 0)
				emptyPos.push_back(i*N+j);
		}

	if(emptyPos.empty())
		return false;

	int value = emptyPos[rand() % emptyPos.size()];
	data[value/N][value%N] = rand() % 10 == 1 ? 4 : 2;
	return true;
}


void Game::restart()
{
	for(int i =0; i<N; ++i)
		for(int j=0; j<N; ++j)
			data[i][j] = 0;
	randNew();
	randNew();
	Status = Status_NORNAL;
}

void Game::processInput()
{
	char ch ;
	ch = getch();
	
	if(ch>='a' && ch <='z')
		ch-=32;
	
	if(Status == Status_NORNAL){	
		bool update = false;
		
		if(ch == 'A')
			update = moveLeft();
		else if(ch == 'D')
			update = moveRight();
		else if(ch == 'W')
			update = moveUp();
		else if(ch == 'S')
			update = moveDown();
		else
			;
		//	Status = (Status+ 1)%3;
		if(update)
			randNew();
		if(isWin())
			Status = Status_WIN;
		if(isDead())
			Status = Status_FAILED;
	}

	if(ch == 'Q')
		Status = Status_QUIT;
	else if(ch == 'R')
		restart();
}

void Game::initArray()
{
	for(int i=0; i<N; ++i)
		for(int j=0; j<N; ++j)
			data[i][j] = 4;
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
