#include "Cell.h"

Cell::Cell(sf::Vector2i position)
{
	state = State::dead;
	this->position = position;

	shape.setFillColor(sf::Color::White);
	shape.setSize(sf::Vector2f(CELL_SIZE, CELL_SIZE));
	shape.setOrigin(sf::Vector2f(CELL_SIZE/2, CELL_SIZE/2));
	shape.setPosition(position.x * CELL_SIZE, position.y * CELL_SIZE);
}

Cell::~Cell()
{
}

State Cell::getState()
{
	return state;
}

void Cell::behaviour(int noNe)
{
	switch (state)
	{
	case State::dead:
		if (noNe == 3)
			setSwapReady();
		break;
	case State::alive:
		if (noNe != 2 && noNe != 3)
			setSwapReady();
		break;
	}
}

void Cell::setSwapReady()
{
	swapReady = true;
}

void Cell::swapState()
{
	if (swapReady)
	{
		switch (state)
		{
		case State::dead:
			state = State::alive;
			break;
		case State::alive:
			state = State::dead;
			break;
		}
		swapReady = false;
	}
}

sf::Vector2i Cell::getPosition()
{
	return position;
}

void Cell::draw(sf::RenderWindow& window)
{
	if (state == State::alive)
		window.draw(shape);
}
