#include "Snake.hpp"

Snake::Snake(int startX, int startY)
{
	body.push_back(Point(startX, startY));
	direction = Direction::RIGHT;
}

Snake::~Snake()
{}

