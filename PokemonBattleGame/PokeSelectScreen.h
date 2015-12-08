#ifndef POKESELECTSCREEN_H
#define POKESELECTSCREEN_H
#include <algorithm>
#include <condition_variable>
#include "SFML\Graphics.hpp"
#include "PokeSelectBox.h"
#include "Pokemon.h"
#include "SFML\System.hpp"
#include "TextureLoader.h"
#include "PokeSelectBoxLarge.h"

class PokeSelectScreen : public sf::Drawable
{
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;//draw the object
	sf::Font font;

	TextureLoader loader;
	sf::RenderTexture screenTex;

	sf::Sprite background;
	sf::Sprite selectScreen;

	std::vector<Pokemon*> *pokemon, *selectedPokemon;
	PokeSelectBox boxes[6];
	PokeSelectBoxLarge selectedBoxes[3];
	int selected, top, partySize;

	bool selecting;

	std::condition_variable cv;

public:
	PokeSelectScreen(const sf::Vector2i WIN_SIZE);
	~PokeSelectScreen();
	void setPokemonList(std::vector<Pokemon*>* p);
	void refresh();
	void keysPressed(std::vector<sf::Keyboard::Key> key);//respond to pressed keys
	void getParty(std::vector<Pokemon*>* pokemon, std::vector<Pokemon*> *selected, int amount);//will block untill the user selects their pokemon. "selected" is where the party is put.
	void getParty(std::vector<Pokemon*>* party, int amount);
};

#endif