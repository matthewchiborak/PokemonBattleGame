#include "BattleBar.h"
#include <iostream>


void BattleBar::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	if (seletingMove)
	{
		target.draw(moveSelect, states);
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
	if (seletingMove)
	{
		
	}
	else
	{	
		arrow.setPosition(selectPositions[selected]);
		std::cout << selected << std::endl;
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

	seletingMove = false;
	selected = 0;
	selectPositions[0] = sf::Vector2f(128,121);
	selectPositions[1] = sf::Vector2f(184, 121);
	selectPositions[2] = sf::Vector2f(128, 137);
	selectPositions[3] = sf::Vector2f(184,137);

	updateArrowPosition();
}

void BattleBar::keyPressed(sf::Keyboard::Key key)
{
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
	updateArrowPosition();
}

void BattleBar::clicked(sf::Vector2i location)
{
}


BattleBar::~BattleBar()
{
}
