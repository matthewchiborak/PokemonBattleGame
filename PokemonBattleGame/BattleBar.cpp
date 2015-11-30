#include "BattleBar.h"
#include <iostream>


void BattleBar::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	switch (state)
	{
	case BattleBar::ACTION:
		target.draw(bar, states);
		target.draw(select, states);
		target.draw(arrow, states);
		break;
	case BattleBar::MOVE:
		target.draw(moveSelect, states);
		target.draw(arrow, states);
		break;
	case BattleBar::TEXT:
		target.draw(bar, states);
		target.draw(displayText, states);
		break;
	default:
		break;
	}
}

void BattleBar::updateArrowPosition()
{
	//update the postion of the arrow based on what screen is being viewed
	if (state == MOVE)
	{
		arrow.setPosition(movePositions[selected]);
	}
	else if (state == ACTION)
	{	
		arrow.setPosition(selectPositions[selected]);
	}
}

BattleBar::BattleBar()
{
	//load textures
	bar.setTexture(*loader.tryLoadTexture("BattleBar", "Resources/BattleBar.png"));
	bar.setPosition(0, 110);

	select.setTexture(*loader.tryLoadTexture("BattleSelect", "Resources/battleSelect.png"));
	select.setPosition(120, 110);

	moveSelect.setTexture(*loader.tryLoadTexture("MoveSelect", "Resources/moveSelect.png"));
	moveSelect.setPosition(0, 110);

	arrow.setTexture(*loader.tryLoadTexture("arrow", "Resources/arrow.png"));
	
	//create wanring for trying to use items
	font.loadFromFile("Resources/EmeraldPro.ttf");
	displayText = PokeText("OAK: Now is not the\n time to use that", sf::Vector2f(18, 118), true, &font, 15);
	displayText.setLightText();

	//save the positions of the arrow
	state = ACTION;
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
	if (state == MOVE || state == ACTION)
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
			//to handle negative values
			selected += 4;
		}
		selected = selected % 4;//to handle values > 3
	}

	if (key == sf::Keyboard::Z)//when Z is pressed (A button)
	{
		if (state == ACTION)
		{
			if ((selected == 0))
			{
				selected = 0;
				state = MOVE;
			}
			if (selected == 1)
			{
				state = TEXT;
				displayText = PokeText("OAK: Now is not the time to use that", sf::Vector2f(18, 118), true, &font, 15);
				displayText.setLightText();
			}
			if (selected == 3)
			{
				state = TEXT;
				displayText = PokeText("Run?", sf::Vector2f(18, 118), true, &font, 15);
				displayText.setLightText();
			}
		}
		else if (state == TEXT)
		{
			state = ACTION;
		}
	}
	if (key == sf::Keyboard::X)// when X is pressed (B button)
	{
		if (state == MOVE)
		{
			selected = 0;
			state = ACTION;
		}
		else if (state == TEXT)
		{
			state = ACTION;
		}
	}

	updateArrowPosition();
}

void BattleBar::clicked(sf::Vector2i location)
{
}


BattleBar::~BattleBar()
{
}
