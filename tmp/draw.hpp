#include <ncurses.h>
#include <deque>

// Initialize colors in your main function or an initialization function:
void initializeColors() 
{
    start_color(); // Active le mode couleur
    init_pair(1, COLOR_GREEN, COLOR_BLACK); 
	init_pair(2, COLOR_RED, COLOR_BLACK); // Nourriture
	init_pair(3, COLOR_YELLOW, COLOR_BLACK); 
}

struct Point 
{ 
	int x; 
	int y;

	Point(int x_, int y_) : x(x_), y(y_) {} 
};

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

void drawSnake(const std::deque<Point>& snake)
{
	if (snake.empty())
		return;

	// Tête du snake
	attron(COLOR_PAIR(1)); 
	mvaddch(snake[0].y, snake[0].x, '@');
	attroff(COLOR_PAIR(1));
	
	// Corps du snake
	for (size_t i = 1; i < snake.size(); ++i)
	{
		mvaddch(snake[i].y, snake[i].x, 'O');
	}
}

void drawFood(const Point& food)
{
	attron(COLOR_PAIR(2)); 
	mvaddch(food.y, food.x, '*');
	attroff(COLOR_PAIR(2));
}
