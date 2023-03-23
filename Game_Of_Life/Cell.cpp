#include "Cell.h"

Cell::Cell(sf::Vector2i position)
{
	state = State::dead;
	shape.setFillColor(sf::Color::White);
	shape.setSize(sf::Vector2f(CELL_SIZE, CELL_SIZE));
	shape.setOrigin(sf::Vector2f(CELL_SIZE/2, CELL_SIZE/2));
	shape.setPosition(position.x * 10, position.y * 10);
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

void Cell::draw(sf::RenderWindow& window)
{
	window.draw(shape);
}
