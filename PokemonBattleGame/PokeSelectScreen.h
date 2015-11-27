#ifndef POKESELECTSCREEN_H
#define POKESELECTSCREEN_H
#include "SFML\Graphics.hpp"
#include "PokeSelectBox.h"
#include "Pokemon.h"
#include "SFML\System.hpp"
class PokeSelectScreen : public sf::Drawable
{
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;//draw the object
	sf::Font font;

	sf::RenderTexture screenTex;

	sf::Texture selectScreenTex;
	sf::Sprite selectScreen;

	std::vector<Pokemon> *pokemon;
	PokeSelectBox boxes[6];
	int selected, top;
public:
	PokeSelectScreen(const sf::Vector2i WIN_SIZE);
	~PokeSelectScreen();
	void setPokemonList(std::vector<Pokemon>* p);
	void refresh();
	void keysPressed(std::vector<sf::Keyboard::Key> key);//respond to pressed keys
};

#endif