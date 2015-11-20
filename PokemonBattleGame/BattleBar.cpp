#include "BattleBar.h"
#include <iostream>


void BattleBar::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	if (selectingMove)
	{
		target.draw(moveSelect, states);
		target.draw(arrow, states);
	}
	else
	{
		target.draw(bar, states);
		target.draw(select, states);
		target.draw(arrow, states);
	}
}

void BattleBar::updateArrowPosition()
{
	if (selectingMove)
	{
		arrow.setPosition(movePositions[selected]);
	}
	else
	{	
		arrow.setPosition(selectPositions[selected]);
	}
}

BattleBar::BattleBar()
{
	//load textures
	barTex.loadFromFile("Resources/BattleBar.png");
	bar.setTexture(barTex);
	bar.setPosition(0, 110);

	selectTex.loadFromFile("Resources/battleSelect.png");
	select.setTexture(selectTex);
	select.setPosition(120, 110);

	moveSelectTex.loadFromFile("Resources/moveSelect.png");
	moveSelect.setTexture(moveSelectTex);
	moveSelect.setPosition(0, 110);

	arrowTex.loadFromFile("Resources/arrow.png");
	arrow.setTexture(arrowTex);

	selectingMove = false;
	selected = 0;
	selectPositions[0] = sf::Vector2f(128,121);
	selectPositions[1] = sf::Vector2f(184, 121);
	selectPositions[2] = sf::Vector2f(128, 137);
	selectPositions[3] = sf::Vector2f(184,137);

	movePositions[0] = sf::Vector2f(9,124);
	movePositions[1] = sf::Vector2f(81,124);
	movePositions[2] = sf::Vector2f(9,140);
	movePositions[3] = sf::Vector2f(81,140);

	updateArrowPosition();
}

void BattleBar::keyPressed(sf::Keyboard::Key key)
{
	//move the arrow
	if (key == sf::Keyboard::Up)
	{
		selected -= 2;
	}
	else if (key == sf::Keyboard::Down)
	{
		selected += 2;
	}
	else if (key == sf::Keyboard::Left)
	{
		selected -= 1;
	}
	else if (key == sf::Keyboard::Right)
	{
		selected += 1;
	}
	if (selected < 0)
	{
		selected += 4;
	}
	selected = selected % 4;

	if (key == sf::Keyboard::Return)
	{
		selected = 0;
		selectingMove = !selectingMove;
	}

	updateArrowPosition();
}

void BattleBar::clicked(sf::Vector2i location)
{
}


BattleBar::~BattleBar()
{
}
