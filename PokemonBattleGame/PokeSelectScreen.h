#ifndef POKESELECTSCREEN_H
#define POKESELECTSCREEN_H
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

	std::vector<Pokemon> *pokemon;
	PokeSelectBox boxes[6];
	PokeSelectBoxLarge largeBox;
	int selected, top;
public:
	PokeSelectScreen(const sf::Vector2i WIN_SIZE);
	~PokeSelectScreen();
	void setPokemonList(std::vector<Pokemon>* p);
	void refresh();
	void keysPressed(std::vector<sf::Keyboard::Key> key);//respond to pressed keys
};

#endif