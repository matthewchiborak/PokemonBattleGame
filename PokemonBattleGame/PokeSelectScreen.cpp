#include "PokeSelectScreen.h"

bool PokeSort(Pokemon *i, Pokemon *j)
{
	return i->getID() < j->getID();
}


void PokeSelectScreen::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	if (selecting)
	{
		target.draw(selectScreen, states);
	}
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
	partySize = 3;

	selectedPokemon = nullptr;
	selecting = false;
}

PokeSelectScreen::~PokeSelectScreen()
{
}

void PokeSelectScreen::setPokemonList(std::vector<Pokemon*>* p)
{
	this->pokemon = p;
	refresh();
}

void PokeSelectScreen::refresh()
{
	if (selecting)
	{
		int index = top;
		for (int i = 0; i < 6 && i < pokemon->size(); i++)
		{
			boxes[i].deselect();
			boxes[i].setPokemon(pokemon->at(index));
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
		if (selectedPokemon != nullptr)
		{
			for (int i = 0; i < partySize && i < selectedPokemon->size(); i++)
			{
				screenTex.draw(selectedBoxes[i]);
			}
		}
		for (int i = 0; i < 6; i++)
		{
			screenTex.draw(boxes[i]);
		}

		screenTex.display();
		selectScreen.setTexture(screenTex.getTexture());
	}
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
		if (keys[i] == sf::Keyboard::Down)			// Fix issue arround setting top near the end of the pokemon list
		{
			selected += 1;
			if (selected >= pokemon->size())		// This is for when the selected pokemon is last one in the list
			{
				selected -= pokemon->size();		// Sets the pokemon to first one
				top = selected;						// Reset the top to the first one
			}
			else if (selected > top + 5)
			{
				top = selected -5;
			}
		}
		if (selectedPokemon != nullptr)
		{
			if (keys[i] == sf::Keyboard::Z)
			{
				if (selectedPokemon->size() < partySize)
				{
					selectedBoxes[selectedPokemon->size()].setPokemon(pokemon->at(selected));
					selectedPokemon->push_back(pokemon->at(selected));
					pokemon->erase(pokemon->begin() + selected);
					if (selected >= pokemon->size())
					{
						selected -= 1;
					}
					if (top >= pokemon->size())
					{
						top -= 1;
					}
				}
				else
				{
					selecting = false;
					cv.notify_all();
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
	}
	refresh();
}

void PokeSelectScreen::getParty(std::vector<Pokemon*>* pokemon, std::vector<Pokemon*> *selected, int amount)
{
	std::mutex mtx;
	std::unique_lock<std::mutex> lock(mtx);
	selectedPokemon = selected;
	setPokemonList(pokemon);
	partySize = amount;
	cv.wait(lock);
}

void PokeSelectScreen::getParty(std::vector<Pokemon*>* party, int amount)
{
	std::mutex mtx;
	std::unique_lock<std::mutex> lock(mtx);
	selectedPokemon = party;
	partySize = amount;
	selecting = true;
	cv.wait(lock);
}
