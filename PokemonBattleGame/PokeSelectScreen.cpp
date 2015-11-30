#include "PokeSelectScreen.h"



void PokeSelectScreen::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(selectScreen, states);
}

PokeSelectScreen::PokeSelectScreen(const sf::Vector2i WIN_SIZE)
{
	screenTex.create(240,160);
	selectScreen.setScale(sf::Vector2f(WIN_SIZE.x / 240, WIN_SIZE.y / 160));
	background.setTexture(*loader.tryLoadTexture("PokeSelectBack", "Resources/PokemonSelectBackground.png"));
	boxes[0].setPosition(sf::Vector2f(88, 10));
	boxes[1].setPosition(sf::Vector2f(88, 34));
	boxes[2].setPosition(sf::Vector2f(88, 58));
	boxes[3].setPosition(sf::Vector2f(88, 82));
	boxes[4].setPosition(sf::Vector2f(88, 106));
	boxes[5].setPosition(sf::Vector2f(88, 130));
	largeBox.setPosition(sf::Vector2f(2, 20));
	top = 0;
	selected = 0;
}

PokeSelectScreen::~PokeSelectScreen()
{
}

void PokeSelectScreen::setPokemonList(std::vector<Pokemon>* p)
{
	this->pokemon = p;
	refresh();
}

void PokeSelectScreen::refresh()
{
	int index = top;
	for (int i = 0; i < 6; i++)
	{
		boxes[i].deselect();
		boxes[i].setPokemon(&pokemon->at(index));
		if (index == selected)
		{
			boxes[i].select();
		}
		index++;
		if (index >= pokemon->size())
		{
			index -= pokemon->size();
		}
	}
	
	screenTex.clear();
	screenTex.draw(background);
	screenTex.draw(largeBox);
	for (int i = 0; i < 6; i++)
	{
		screenTex.draw(boxes[i]);
	}
	
	screenTex.display();
	selectScreen.setTexture(screenTex.getTexture());
}

void PokeSelectScreen::keysPressed(std::vector<sf::Keyboard::Key> keys)
{
	for (int i = 0; i < keys.size(); i++)
	{
		if (keys[i] == sf::Keyboard::Up)
		{
			selected -= 1;
			if (selected < 0)
			{
				selected += pokemon->size();
				top = selected;
			}
			if (selected < top)
			{
				top = selected;
			}
			largeBox.setPokemon(&pokemon->at(selected));
		}
		if (keys[i] == sf::Keyboard::Down)//fix issue arround setting top near the end of the pokemon list
		{
			selected += 1;
			if (selected >= pokemon->size())
			{
				selected -= pokemon->size();
				top = selected;
			}
			else if (selected > top + 5)
			{
				top = selected -5;
			}
			largeBox.setPokemon(&pokemon->at(selected));
		}
	}
	refresh();
}
