#include <ncurses.h>

void	drawTopWall(int width)
{
	int x = 0;
	int y = 0;
	for(int i = 0; i < width; ++i)
	{
		x = i;
		mvaddch(y, x, '#');
	}
}

void	drawBottomWall(int width, int height)
{
	int x = 0;
	int y = height - 1;
	for(int i = 0; i < width; ++i)
	{
		x = i;
		mvaddch(y, x, '#');
	}
}

void	drawLeftWall(int height)
{
	int x = 0;
	for(int y = 0; y < height - 1; ++y)
	{
		mvaddch(y, x, '#');
	}
}

void	drawRightWall(int width, int height)
{
	int x = width -1 ;
	for(int y = 0; y < height - 1; ++y)
	{
		mvaddch(y, x, '#');
	}
}

void	drawWalls(int width, int height)
{
	drawTopWall(width);
	drawBottomWall(width, height);
	drawLeftWall(height);
	drawRightWall(width, height);
}
