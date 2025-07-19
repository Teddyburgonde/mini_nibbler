#include <deque>
#include <iostream>

struct Point {
	int	x;
	int	y;
};

enum class Direction {
	UP,
	DOWN,
	LEFT,
	RIGHT,
};


class Snake {
	public:
		Snake(int startX, int startY);
		~Snake();
		void move();
		void grow();
		bool checkCollision(const Point& pos) const;
		const std::deque<Point>& getBody() const;


	private:
		std::deque<Point> body;
		Direction direction;
};