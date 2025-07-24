#pragma once

/**
 * @brief Structure représentant un point en 2D.
 */
struct Point
{
	int x;
	int y;

	Point(int x_, int y_) : x(x_), y(y_) {}
	Point() : x(0), y(0) {}
};