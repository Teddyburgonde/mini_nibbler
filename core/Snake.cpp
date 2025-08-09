#include "Snake.hpp"

/**
 * @brief Constructeur du Snake : initialise le serpent avec 4 segments alignés horizontalement vers la gauche.
 *
 * La tête est placée aux coordonnées de départ, et 3 segments supplémentaires
 * sont ajoutés derrière elle, dans la direction opposée au mouvement initial.
 *
 * @param startX Position X de départ de la tête.
 * @param startY Position Y de départ de la tête.
 */
Snake::Snake(int startX, int startY) : direction(Direction::RIGHT)
{
	body.push_front({startX, startY});
	body.push_back({startX - 1, startY});
	body.push_back({startX - 2, startY}); 
	body.push_back({startX - 3, startY});
}

/**
 * @brief Destructeur par défaut
 */
Snake::~Snake() {}

/**
 * @brief Déplace le serpent dans la direction actuelle
 */
void Snake::move()
{
	Point head = body.front();

	switch (direction)
	{
		case Direction::UP:    
			head.y -= 1; 
			break;
		case Direction::DOWN:
		 	head.y += 1;
			break;
		case Direction::LEFT:
		 	head.x -= 1;
			break;
		case Direction::RIGHT:
			head.x += 1;
			break;
	}

	body.push_front(head); // Ajoute la nouvelle tête
	body.pop_back(); // Supprime l'ancienne queue
}

/**
 * @brief Fait grandir le serpent (ajoute un nouveau point sans retirer la queue)
 */
void Snake::grow()
{
	Point head = body.front();

	switch (direction)
	{
		case Direction::UP:
			head.y -= 1;
			break;
		case Direction::DOWN:
			head.y += 1;
			break;
		case Direction::LEFT:
			head.x -= 1;
			break;
		case Direction::RIGHT:
			head.x += 1;
			break;
	}

	body.push_front(head);
}

/**
 * @brief Vérifie si la position donnée entre en collision avec le corps du serpent
 */
bool Snake::checkCollision(const Point& pos, bool ignoreHead) const
{
	size_t start = ignoreHead ? 1 : 0;
	for (size_t i = start; i < body.size(); ++i)
	{
		if (body[i].x == pos.x && body[i].y == pos.y)
			return true;
	}
	return false;
}

/**
 * @brief Retourne le corps complet du serpent (en lecture seule)
 */
const std::deque<Point>& Snake::getBody() const
{
	return body;
}

/**
 * @brief Change la direction du serpent, sauf si la nouvelle direction est l'opposée de l'actuelle.
 *
 * Cette fonction empêche le serpent de faire demi-tour instantanément,
 * ce qui provoquerait une collision avec lui-même.
 *
 * @param newDir La nouvelle direction demandée.
 */
void Snake::setDirection(Direction newDir)
{
	if ((direction == Direction::UP &&
		newDir == Direction::DOWN) ||
        (direction == Direction::DOWN  
		&& newDir == Direction::UP) ||
        (direction == Direction::LEFT  
		&& newDir == Direction::RIGHT) ||
        (direction == Direction::RIGHT && 
		newDir == Direction::LEFT))
    {
        return;
    }
	direction = newDir;
}
