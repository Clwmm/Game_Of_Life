#pragma once
#include "SFML/Graphics.hpp"

#define CELL_SIZE 5

enum class State{ dead, alive};

class Cell
{
private:
	bool swapReady = false;
	State state;
	sf::Vector2i position;

	sf::RectangleShape shape;

public:
	Cell(sf::Vector2i position);
	~Cell();
	State getState();
	void behaviour(int noNe);
	void setSwapReady();
	void swapState();
	sf::Vector2i getPosition();

	void draw(sf::RenderWindow& window);
};

