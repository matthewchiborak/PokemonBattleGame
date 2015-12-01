#include "PokeSelectScreen.h"

bool PokeSort(Pokemon i, Pokemon j)
{
	return i.getID() < j.getID();
}


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
	selectedBoxes[0].setPosition(sf::Vector2f(2,1));
	selectedBoxes[1].setPosition(sf::Vector2f(2,51));
	selectedBoxes[2].setPosition(sf::Vector2f(2,101));
	top = 0;
	selected = 0;

	selectedPokemon = new std::vector<Pokemon>;
}

PokeSelectScreen::~PokeSelectScreen()
{
	delete selectedPokemon;
}

void PokeSelectScreen::setPokemonList(std::vector<Pokemon>* p)
{
	this->pokemon = p;
	refresh();
}

void PokeSelectScreen::refresh()
{
	int index = top;
	for (int i = 0; i < 6 && i < pokemon->size(); i++)
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
	for (int i = 0; i < 3 && i < selectedPokemon->size(); i++)
	{
		screenTex.draw(selectedBoxes[i]);
	}
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
		}
		if (keys[i] == sf::Keyboard::Z)
		{
			if (selectedPokemon->size() < 3)
			{
				selectedBoxes[selectedPokemon->size()].setPokemon(&pokemon->at(selected));
				selectedPokemon->push_back(pokemon->at(selected));
				pokemon->erase(pokemon->begin()+selected);
				if (selected >= pokemon->size())
				{
					selected -=1;
				}
				if (top >= pokemon->size())
				{
					top -=1;
				}
			}

		}
		if (keys[i] == sf::Keyboard::X)
		{
			if (selectedPokemon->size() > 0)
			{
				pokemon->push_back(selectedPokemon->back());
				selectedPokemon->pop_back();
				std::sort(pokemon->begin(), pokemon->end(), PokeSort);
			}
		}
	}
	refresh();
}
