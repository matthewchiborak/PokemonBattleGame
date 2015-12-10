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
	case BattleBar::MOVESELECTED:
		target.draw(moveSelect, states);
		target.draw(arrow, states);
		target.draw(moveText[0], states);
		target.draw(moveText[1], states);
		target.draw(moveText[2], states);
		target.draw(moveText[3], states);
		target.draw(moveSelectFrame,states);
		target.draw(PP, states);
		target.draw(moveType, states);
		break;
	case BattleBar::TEXT:
		target.draw(bar, states);
		target.draw(displayText, states);
		break;
	default:
		target.draw(bar, states);
		target.draw(select, states);
		target.draw(arrow, states);
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

	moveSelectFrame.setTexture(*loader.tryLoadTexture("MoveSelectFrame","Resources/moveSelectFrame.png"));
	moveSelectFrame.setPosition(0, 110);

	arrow.setTexture(*loader.tryLoadTexture("arrow", "Resources/arrow.png"));

	//create wanring for trying to use items
	font.loadFromFile("Resources/EmeraldPro.ttf");
	displayText = PokeText("OAK: Now is not the\n time to use that", sf::Vector2f(18, 118), true, &font, 15);
	displayText.setLightText();

	//create Move text
	moveText[0] = PokeText("Move1", sf::Vector2f(12,117), true, &font, 16);
	moveText[1] = PokeText("Move2", sf::Vector2f(89,117), true, &font, 16);
	moveText[2] = PokeText("Move3", sf::Vector2f(12,133), true, &font, 16);
	moveText[3] = PokeText("Move4", sf::Vector2f(89,133), true, &font, 16);

	PP = PokeText("40  40", sf::Vector2f(202,115), true, &font, 16);
	moveType = PokeText("NORMAL", sf::Vector2f(192,132), true, &font, 16);

	//save the positions of the arrow
	state = ACTION;
	selected = 0;
	selectPositions[0] = sf::Vector2f(128,121);
	selectPositions[1] = sf::Vector2f(184, 121);
	selectPositions[2] = sf::Vector2f(128, 137);
	selectPositions[3] = sf::Vector2f(184,137);

	movePositions[0] = sf::Vector2f(6,124);
	movePositions[1] = sf::Vector2f(83,124);
	movePositions[2] = sf::Vector2f(6,140);
	movePositions[3] = sf::Vector2f(83,140);

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
		if (state == MOVE)
		{
			moveType.setText(moves[selected]->getType());
			int cPP = moves[selected]->getCurrentPP();
			int maxPP = moves[selected]->getMaxPP();
			std::stringstream s;
			if (cPP < 10)
			{
				s << "  " << cPP;
			}
			else
			{
				s << cPP;
			}
			s << "  ";
			if (maxPP < 10)
			{
				s << " " << maxPP;
			}
			else
			{
				s << maxPP;
			}
			PP.setText(s.str());
		}
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
			if (selected == 2)
			{
				//when the user wants to select a pokemon
				state = SELECTION;
			}
			if (selected == 3)
			{
				state = TEXT;
				displayText = PokeText("No! There's no running\nfrom a TRAINER battle!", sf::Vector2f(18, 118), true, &font, 15);
				displayText.setLightText();
			}
		}
		else if (state == MOVE)
		{
			state = MOVESELECTED;
		}
		else if (state == TEXT)
		{
			state = ACTION;
			cv.notify_all();
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

void BattleBar::setMoves(Pokemon * p)//updates the move texts and saves the moves from the given pokemon
{
	moves[0] = p->getMove(1);
	moves[1] = p->getMove(2);
	moves[2] = p->getMove(3);
	moves[3] = p->getMove(4);

	moveText[0].setText(moves[0]->getName());
	moveText[1].setText(moves[1]->getName());
	moveText[2].setText(moves[2]->getName());
	moveText[3].setText(moves[3]->getName());
	this->pokemon = p;
}

void BattleBar::resetState()
{
	selected = 0;// set the selected positino to the upper left
	state = ACTION;//set the state to ACTION (selecting Fight,Pokemon, "Bag" or "Run")
	updateArrowPosition();//update the position of the arrow
}

BattleBar::states BattleBar::getState()
{
	return state;
}

int BattleBar::getSelection()
{
	return selected;
}

void BattleBar::showMessage(std::string message)
{
	std::mutex mtx;
	std::unique_lock<std::mutex> lock(mtx);
	state = TEXT;
	displayText = PokeText(message, sf::Vector2f(18, 118), true, &font, 15);
	displayText.setLightText();
	cv.wait(lock);
}


BattleBar::~BattleBar()
{
}
